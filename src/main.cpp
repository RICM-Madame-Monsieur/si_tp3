#include <iostream>
#include <vector>
#include <string>

#include <shader.h> // Help to load shaders from files

// Include GLEW : Always include it before glfw.h et gl.h :)
#include <GL/glew.h>    // OpenGL Extension Wrangler Library : http://glew.sourceforge.net/ 
#include <GL/glfw.h>    // Window, keyboard, mouse : http://www.glfw.org/

#include <glm/glm.hpp>  // OpenGL Mathematics : http://glm.g-truc.net/0.9.5/index.html
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include <GLFW_define.h>
#include <Mesh.h>

// Dimensions de la fenêtre :
#define WIDTH 1000.0f
#define HEIGHT 800.0f

using namespace glm;
using namespace std;


void view_control(mat4& view_matrix, float dx);

int main()
{

    cout << "Debut du programme..." << endl;

    //==================================================
    //============= Creation de la fenetre =============
    //==================================================


    // Initialisation de GLFW
	if( !glfwInit() )
	{
		cout << "Echec de l'initialisation de GLFW" << endl;
		exit(EXIT_FAILURE);
	}

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 16); // Anti Aliasing
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); // OpenGL 3.1
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

    // Ouverture d'une fenêtre en 1024x768
    // et creation d'un contexte OpenGL
    if( !glfwOpenWindow(WIDTH, HEIGHT, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		cout << "Echec de l'ouverture de fenetre OpenGL" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
    }

    // Definition du titre de la fenêtre
	glfwSetWindowTitle( "Polytech RICM 4 - TP3" );

    // Autorise GLFW a recevoir les appuis de touche
	glfwEnable( GLFW_STICKY_KEYS );

    // Initialisation de  GLEW
	if (glewInit() != GLEW_OK) {
		cout << "Echec de l'initialisation de GLEW" << endl;
		exit(EXIT_FAILURE);
	}

    // Verification des donnees du contexte OpenGL
    const GLubyte* renderer = glGetString (GL_RENDERER);
    cout << "Carte Graphique : " << renderer << endl;

    const GLubyte* version = glGetString (GL_VERSION);
    cout << "Driver OpenGL : " << version << endl;


    //==================================================
    //================= Initialisation =================
    //==================================================

    cout << "Initialisations..." << endl;


    // Definition de la couleur du fond
    glClearColor(0.1, 0.1, 0.1, 0.0);

    // Activation du test de profondeur
    glEnable(GL_DEPTH_TEST);

    // Activation du culling
    glEnable(GL_CULL_FACE);


//-------------------------------------------------
// Initialisation du shader programm

    // Compilation du shader programm
	GLuint programID = LoadShaders( "../shader/vertex.glsl", "../shader/fragment.glsl" );
    cout << "programID = " << programID << endl;

	// Obtention de l'ID de l'attribut "in_position" dans programID
	GLuint vertexPositionID = glGetAttribLocation(programID, "in_position");
    cout << "vertexPositionID = " << vertexPositionID << endl;



//-------------------------------------------------
// Initialisation des arrays de données


    // Definition d'un tableau de vecteurs
    vector<vec3> vertices;
    vertices.push_back(vec3(-1, -1, -1));
    vertices.push_back(vec3( 1,  1, -1));
    vertices.push_back(vec3( 1, -1, -1));
    vertices.push_back(vec3(-1, -1, -1));
    vertices.push_back(vec3(-1,  1, -1));
    vertices.push_back(vec3( 1,  1, -1));

    vertices.push_back(vec3(-1, -1, -1));
    vertices.push_back(vec3(-1,  1,  1));
    vertices.push_back(vec3(-1,  1, -1));
    vertices.push_back(vec3(-1, -1, -1));
    vertices.push_back(vec3(-1, -1,  1));
    vertices.push_back(vec3(-1,  1,  1));

    vertices.push_back(vec3(-1, -1, -1));
    vertices.push_back(vec3( 1, -1,  1));
    vertices.push_back(vec3(-1, -1,  1));
    vertices.push_back(vec3(-1, -1, -1));
    vertices.push_back(vec3( 1, -1, -1));
    vertices.push_back(vec3( 1, -1,  1));

    vertices.push_back(vec3( 1,  1,  1));
    vertices.push_back(vec3(-1,  1,  1));
    vertices.push_back(vec3(-1, -1,  1));
    vertices.push_back(vec3( 1,  1,  1));
    vertices.push_back(vec3(-1, -1,  1));
    vertices.push_back(vec3( 1, -1,  1));

    vertices.push_back(vec3( 1,  1,  1));
    vertices.push_back(vec3( 1, -1,  1));
    vertices.push_back(vec3( 1, -1, -1));
    vertices.push_back(vec3( 1,  1,  1));
    vertices.push_back(vec3( 1, -1, -1));
    vertices.push_back(vec3( 1,  1, -1));

    vertices.push_back(vec3( 1,  1,  1));
    vertices.push_back(vec3( 1,  1, -1));
    vertices.push_back(vec3(-1,  1, -1));
    vertices.push_back(vec3( 1,  1,  1));
    vertices.push_back(vec3(-1,  1, -1));
    vertices.push_back(vec3(-1,  1,  1));

    // Creation d'un vertex buffer (VBO) avec vertexBufferID pour identifiant
    GLuint vertexBufferID;
    glGenBuffers(1, &vertexBufferID);
    cout << "vertexBufferID = " << vertexBufferID << endl;

    // Definition de vertexBufferID comme le buffer courant
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

    // Copie des donnees sur la carte graphique (dans vertexBufferID)
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);



    //==================================================
    // Todo 1 : Creation d'un nouveau buffer pour la couleur
    //==================================================

    vector<vec4> colors;
    colors.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
    colors.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
    colors.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
    colors.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
    colors.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
    colors.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));

    colors.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));

    colors.push_back(vec4(1.0f, 0.0f, 1.0f, 1.0f));
    colors.push_back(vec4(1.0f, 0.0f, 1.0f, 1.0f));
    colors.push_back(vec4(1.0f, 0.0f, 1.0f, 1.0f));
    colors.push_back(vec4(1.0f, 0.0f, 1.0f, 1.0f));
    colors.push_back(vec4(1.0f, 0.0f, 1.0f, 1.0f));
    colors.push_back(vec4(1.0f, 0.0f, 1.0f, 1.0f));

    colors.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));
    colors.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));
    colors.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));
    colors.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));
    colors.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));
    colors.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));

    colors.push_back(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    colors.push_back(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    colors.push_back(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    colors.push_back(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    colors.push_back(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    colors.push_back(vec4(1.0f, 1.0f, 1.0f, 1.0f));

    colors.push_back(vec4(1.0f, 1.0f, 0.0f, 1.0f));
    colors.push_back(vec4(1.0f, 1.0f, 0.0f, 1.0f));
    colors.push_back(vec4(1.0f, 1.0f, 0.0f, 1.0f));
    colors.push_back(vec4(1.0f, 1.0f, 0.0f, 1.0f));
    colors.push_back(vec4(1.0f, 1.0f, 0.0f, 1.0f));
    colors.push_back(vec4(1.0f, 1.0f, 0.0f, 1.0f));

    GLuint colorBufferID;

    // création d'un nouveau buffer
    glGenBuffers(1, &colorBufferID);

    // définition de celui-ci comme le buffer courant
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);

    // recopie des données de "colors" dans le buffer courant
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(vec4), colors.data(), GL_STATIC_DRAW);

    GLuint colorPositionID = glGetAttribLocation(programID, "in_color");

    //==================================================
    // Todo 2 : Creation d'un nouveau buffer pour les indices
    //==================================================

    vector<uint> indices;
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(4);
    indices.push_back(5);

    GLuint indiceBufferID;

    // création d'un nouveau buffer
    glGenBuffers(1, &indiceBufferID);

    // définition de celui-ci comme le buffer courant
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferID);

    // recopie des données de "colors" dans le buffer courant
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), indices.data(), GL_STATIC_DRAW);

    //==================================================
    // Todo 3 : Creation des buffers avec le chargement d'un maillage
    //==================================================








//-------------------------------------------------
// Initialisation des matrices MVP


    // Definition des matrices de transformation
    mat4 projection_matrix = perspective(45.0f, WIDTH / HEIGHT, 0.1f, 100.0f);
    mat4 view_matrix = lookAt(vec3(0.0, 0.0, 2), vec3(0.0), vec3(0.0, 1.0, 0.0));
    mat4 model_matrix = scale(vec3(1.0f) * 0.5f);

    GLuint PmatrixID = glGetUniformLocation(programID, "ProjectionMatrix");
    cout << "PmatrixID = " << PmatrixID << endl;

    GLuint VmatrixID = glGetUniformLocation(programID, "ViewMatrix");
    cout << "VmatrixID = " << VmatrixID << endl;

    GLuint MmatrixID = glGetUniformLocation(programID, "ModelMatrix");
    cout << "MmatrixID = " << MmatrixID << endl;





    //==================================================
    //=========== Debut des choses serieuses ===========
    //==================================================


    cout << "Debut de la boucle principale..." << endl;

    double init_time = glfwGetTime();
    double prec_time = init_time;
    double cur_time = init_time;
    double speed = 0.5;

    // Boucle de dessin
	do{
        // Nettoyage de la zone de dessin
		glClear( GL_DEPTH_BUFFER_BIT );
		glClear( GL_COLOR_BUFFER_BIT );


        //==================================================
        //============= Calcul du Point de Vue =============
        //==================================================

        prec_time = cur_time;
        cur_time = glfwGetTime() - init_time;
        double delta_time = cur_time - prec_time;

        glfwSetWindowTitle( (string("Polytech RICM 4 - TP3 - ") + detail::format("%2.0f", 1.0/ delta_time) + string(" FPS")).c_str() );

        view_control(view_matrix, speed * delta_time);


        //==================================================
        //===================== Dessin =====================
        //==================================================

		// Definition de programID comme le shader courant
		glUseProgram(programID);

        // Transmission des matrices au vertex shader
        glUniformMatrix4fv(PmatrixID, 1, GL_FALSE, value_ptr(projection_matrix));
        glUniformMatrix4fv(VmatrixID, 1, GL_FALSE, value_ptr(view_matrix));
        glUniformMatrix4fv(MmatrixID, 1, GL_FALSE, value_ptr(model_matrix));



        // Activation de l'attribut vertexPositionID
		glEnableVertexAttribArray(vertexPositionID);

        //==================================================
        // Todo : Activez les attributs que vous avez cree
        //==================================================

        //  activation de l'attribut colorPositionID
        glEnableVertexAttribArray(colorPositionID);

        // Définition de colorBufferID comme le buffer courant
        glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);

        // On indique comment lire les donnée
        glVertexAttribPointer(
            colorPositionID,
            4,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );

        // Definition de vertexBufferID comme le buffer courant
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

        // On indique comment lire les donnees
		glVertexAttribPointer(
            vertexPositionID,   // ID de l'attribut à configurer
            3,                  // nombre de composante par position (x, y, z)
            GL_FLOAT,           // type des composantes
            GL_FALSE,           // normalisation des composantes
            0,                  // decalage des composantes
            (void*)0            // offset des composantes
		);


        //==================================================
        // Todo : Transmettre les buffers que vous avez cree
        //==================================================

        // Definition de indiceBufferID comme le buffer courant
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferID);
         








        //==================================================
        // Todo : Appeller la fonction de dessin par indexation (a la place de celle-ci)
        //==================================================

        // On dit a OpenGL de dessiner le contenu du buffer courant
        //glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        // Dessine les triangles
        glDrawElements(
            GL_TRIANGLES,
            indices.size(),
            GL_UNSIGNED_INT,
            (void*)0
        );





        // Desactivation des attributs
		glDisableVertexAttribArray(vertexPositionID);


        //==================================================
        // Todo : Desactivez les attributs que vous avez cree
        //=================================================

        glDisableVertexAttribArray(colorPositionID);









		// Echange des zones de dessin buffers
		glfwSwapBuffers();

        cout << "Temps ecoule (s) : " << cur_time << "\r";
        cout.flush();

    } // Execution de la boucle...
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&  // ... jusqu'a appui sur la touche ESC
           glfwGetWindowParam( GLFW_OPENED )        );  // ... ou fermeture de la fenetre

    cout << endl;

    // Ferme GLFW et OpenGL
	glfwTerminate();



    //==================================================
    //============== Nettoyage la memoire ==============
    //==================================================

    // Liberation des buffers
    glDeleteBuffers(1, &vertexBufferID);


    //==================================================
    // Todo : Libérer TOUT les buffers que vous avez cree
    //==================================================

    glDeleteBuffers(1, &colorBufferID);






    cout << "Fin du programme..." << endl;


	return EXIT_SUCCESS;
}

void view_control(mat4& view_matrix, float dx)
{
    if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS)
    {
        vec4 axis = vec4(1.0, 0.0, 0.0, 0.0);
        axis = inverse(view_matrix) * axis;
        view_matrix = rotate(view_matrix, dx * 180.0f, vec3(axis));
    }
    if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS)
    {
        vec4 axis = vec4(1.0, 0.0, 0.0, 0.0);
        axis = inverse(view_matrix) * axis;
        view_matrix = rotate(view_matrix, -dx * 180.0f, vec3(axis));
    }
    if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS)
    {
        vec4 axis = vec4(0.0, 1.0, 0.0, 0.0);
        axis = inverse(view_matrix) * axis;
        view_matrix = rotate(view_matrix, dx * 180.0f, vec3(axis));
    }
    if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS)
    {
        vec4 axis = vec4(0.0, 1.0, 0.0, 0.0);
        axis = inverse(view_matrix) * axis;
        view_matrix = rotate(view_matrix, -dx * 180.0f, vec3(axis));
    }
    if (glfwGetKey( GLFW_KEY_PAGEUP ) == GLFW_PRESS)
    {
        vec4 axis = vec4(0.0, 0.0, 1.0, 0.0);
        axis = inverse(view_matrix) * axis;
        view_matrix = rotate(view_matrix, dx * 180.0f, vec3(axis));
    }
    if (glfwGetKey( GLFW_KEY_PAGEDOWN ) == GLFW_PRESS)
    {
        vec4 axis = vec4(0.0, 0.0, 1.0, 0.0);
        axis = inverse(view_matrix) * axis;
        view_matrix = rotate(view_matrix, -dx * 180.0f, vec3(axis));
    }

    if (glfwGetKey( GLFW_KEY_Z ) == GLFW_PRESS)
    {
        vec4 axis = vec4(0.0, 0.0, 1.0, 0.0) * dx;
        axis = inverse(view_matrix) * axis;
        view_matrix = translate(view_matrix, vec3(axis));
    }
    if (glfwGetKey( GLFW_KEY_S ) == GLFW_PRESS)
    {
        vec4 axis = vec4(0.0, 0.0, 1.0, 0.0) * (-dx);
        axis = inverse(view_matrix) * axis;
        view_matrix = translate(view_matrix, vec3(axis));
    }
    if (glfwGetKey( GLFW_KEY_Q) == GLFW_PRESS)
    {
        vec4 axis = vec4(-1.0, 0.0, 0.0, 0.0) * dx;
        axis = inverse(view_matrix) * axis;
        view_matrix = translate(view_matrix, vec3(axis));
    }
    if (glfwGetKey( GLFW_KEY_D ) == GLFW_PRESS)
    {
        vec4 axis = vec4(-1.0, 0.0, 0.0, 0.0) * (-dx);
        axis = inverse(view_matrix) * axis;
        view_matrix = translate(view_matrix, vec3(axis));
    }
    if (glfwGetKey( GLFW_KEY_A ) == GLFW_PRESS)
    {
        vec4 axis = vec4(0.0, 1.0, 0.0, 0.0) * dx;
        axis = inverse(view_matrix) * axis;
        view_matrix = translate(view_matrix, vec3(axis));
    }
    if (glfwGetKey( GLFW_KEY_E ) == GLFW_PRESS)
    {
        vec4 axis = vec4(0.0, 1.0, 0.0, 0.0) * (-dx);
        axis = inverse(view_matrix) * axis;
        view_matrix = translate(view_matrix, vec3(axis));
    }
}

