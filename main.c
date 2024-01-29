/***********************************************************************
*
* @Propòsit: Crear un programa que ajudi a gestionar aquestes 
*             noves millores en el parc de bombers de Prog City.
* @Autor:                        David Susagna Holgado
* @Data de creació:              15/11/2022
* @Data de l'última modificació: 18/11/2022
*
***********************************************************************/
// Llibreries del sistema
#include <stdio.h>
#include <math.h>

// Constants
#define MAXLONGITUD 180      // Longitud màxima del GPS.
#define MAXLATITUD 90        // Latitud màxima del GPS.
#define RANGE1 100           // Ranc d'acció de l'equip A.
#define RANGE2 500           // Ranc d'acció de l'equip B.
#define R 6371               // Radi mitjà de la Terra.
#define PI 3.14159265        // Número Pi
#define MAXTEAMS 3           // Quantitat de grups disponibles.


// Procediments i funcions
/***********************************************************************
*
* @Finalitat:  Passar minúscules a majúscules.
* @Paràmetres: in: a = Caràcter que ha de passar a majúscules.
* @Retorn:     Retorna el caràcter amb format majúscula.
*
***********************************************************************/
char tinyToCapital(char a){

    if (('z' >= a) &&  ('a' <= a)){
        a = a - ('a'-'A');
    }
    return(a);
}

/***********************************************************************
*
* @Finalitat:  Converteix un valor de coma flotant de graus a radians.
* @Paràmetres: in: degrees = Valor amb coma flotant el qual indica el valor en graus.
* @Retorn:     Retorna la distància en radians.
*
***********************************************************************/
float degreesToRadians(float degrees){

    float radians = 0.0;

    radians = (degrees * (PI/180));

    return(radians);
}

/***********************************************************************
*
* @Finalitat:  Demanant que s’introdueixi la longitud del parc de bombers
* @Paràmetres: ----. 
* @Retorn:     Retorna un valor amb coma flotant amb la longitud dins els paràmetres.
*
***********************************************************************/
float scanLongitude(){

	float longitud = 0.0;             // Longitud que registra el GPS.

	// Verificació longitud.
	do{
	    printf("Longitude? ");
	    scanf("%f", &longitud);
    } while((-MAXLONGITUD > longitud) || (MAXLONGITUD < longitud));

    return(longitud);
}
/***********************************************************************
*
* @Finalitat:  Demanant que s’introdueixi la latitud del parc de bombers
* @Paràmetres: ----. 
* @Retorn:     Retorna un valor amb coma flotant amb la latitud dins els paràmetres.
*
***********************************************************************/
float scanLatitude(){

	float latitud = 0.0;              // Latitud que registra el GPS.

    // Verificació latitud.
    do{
	    printf("Latitude? ");
	    scanf("%f", &latitud);
    } while((-MAXLATITUD > latitud) || (MAXLATITUD < latitud));

    return(latitud);
}

/***********************************************************************
*
* @Finalitat:  Mostra per pantalla el menú inicial i sol·licita una opció a l'usuari.
* @Paràmetres: ----. 
* @Retorn:     Retorna l'opció seleccionada per l'usuari.
*
***********************************************************************/
char menu(){
   
    char option = ' ';
    char trash;            // Variable auxiliar per netejar el buffer

    do{
        printf("N - New fire | E - End fire | V - View Teams | A - Add member | Q - Quit \n");
        printf("Enter option: ");
        scanf("%c", &trash);
        scanf("%c", &option);

        // Passar minúscules a majúscules
        option = tinyToCapital(option);

        // Output. El programa mostra un error si l'opció no és vàlida.
        if(('N' != option) && ('E' != option) && ('V' != option) && ('A' != option) && ('Q' != option)){
        	printf("ERROR (Invalid option)\n\n");
        }
    } while(('N' != option) && ('E' != option) && ('V' != option) && ('A' != option) && ('Q' != option)); 
    
    return(option);
}

/***********************************************************************
*
* @Finalitat:  Inicialitza els arrays necessàries per al programa.
* @Paràmetres: in: team[] = Representa la quantia de bombers de cada equip.
*              in: name[] = Representa el nom de cada equip, es reserva la primera posició per com auxiliar.
*              in: operations[] = Representa les operacions actives cada equip.
* @Retorn:     ----.
*
***********************************************************************/
void startArrays(int team[], char name[], int operations[]){

    int i = 0;                        // Variable auxiliar índex.

    // Inicia array corresponent als bombers.
    for(i=1; i<MAXTEAMS; i++){
        team[0] = MAXTEAMS;
        team[i] = team[i-1] -1;
    } 

    // Inicia array corresponent al nom.
    for(i=2; i<(MAXTEAMS + 1); i++){
        name[1] = 'A';
        name[i] = name[i-1] + 1;
    } 

    // Inicia array corresponent a les operacions.
    for(i=0; i<MAXTEAMS; i++){
        operations[i] = 0;
    }
}

/***********************************************************************
*
* @Finalitat:  Dona la benvinguda i sol·licita les dades del GPS a l'usuari.
* @Paràmetres: in: gps[] = Dades del GPS. 
* @Retorn:     ----.
*
***********************************************************************/

void programStart(float gps[]){

    // Output. Donant la benvinguda.
    printf("Welcome to Prog City! \n\n");

    // Output. Demanar la ubicació del parc de bombers.
    printf("Enter current position: \n");
    gps[0] = scanLongitude();
    gps[1] = scanLatitude();
    printf("\n");

}

/***********************************************************************
*
* @Finalitat:  Sol·licita les coordenades del foc i calcula la distància respecte al parc de bombers.
* @Paràmetres: in: station[] = Representa la ubicació del parc de bombers.
* @Retorn:     Retorna la distància del foc al part de bombers.
*
***********************************************************************/
float fireLocated(float station[]){

	float aux1 = 0.0, aux2 = 0.0;
    float lon2 = 0.0, lat2 = 0.0, lon1 = 0.0, lat1 = 0.0;  // Variables corresponents a la longitud i latitud.
	float distance = 0.0;                                  // Distància entre l'estació de bombers i el foc.

    // Ubicació de l'incendi.
	lon2 = scanLongitude();
    lat2 = scanLatitude();

    // Passa de graus a radians
    lon1 = degreesToRadians(station[0]);
    lat1 = degreesToRadians(station[1]);
    lon2 = degreesToRadians(lon2);
    lat2 = degreesToRadians(lat2);

    // Càlcul de la distància.
    aux1 = (pow(sin((lat2 - lat1)/2),2));
    aux2 = (pow(sin((lon2 - lon1)/2),2));
    distance = (2 * R * asin(sqrt( aux1 + (cos(lat1) * cos(lat2) * aux2) )));

    // Output: Imprimeix la distància a la qual es troba l'incendi.
    printf("Fire located at %.0fkm \n", distance);
	return(distance);
}

/***********************************************************************
*
* @Finalitat:   Indica l'equip seleccionat en funció la distància de l'incendi.
* @Paràmetres:  in: name[] = Indica el nom dels grups.
*               in: distance = La distància a la qual es troba l'incendi.
* @Retorn:      ----.
*
***********************************************************************/
void teamSelection(char name[], float distance){

    if((0 <= distance) && (distance <= RANGE1)){
        name[0] = name[1];
    }
    else{
        if((RANGE1 < distance) && (distance <= RANGE2)){
            name[0] = name[2];
        }
        else{
            name[0] = name[3];
        }
    }

}

/***********************************************************************
*
* @Finalitat:  Selecciona la posició dins la array en funció del nom del grup seleccionat.
* @Paràmetres: in: team_name[] = Indica el nom dels grups.
* @Retorn:     Retorna un valor enter el qual índica la possessió dins l'array.
*
***********************************************************************/
int setIndex(char team_name[]){

    int team = 0;    // Indicador de l'equip al qual correspon el caràcter introduït.

    switch(team_name[0]){
        case 'A':
            team = 0;
            break;
        case 'B':
            team = 1;
            break;
        case 'C':
            team = 2;
            break;
        default:
            break;
    }
    return (team);
}

/***********************************************************************
*
* @Finalitat:   Actualitzar el nombre de bombes dins d'un equip.
* @Paràmetres:  in: option = Selecciona una de les dues funcionalitats de la funció.
*               in: team[] = Indica el nombre de bombers disponibles en cada un dels equips.
*               in: name[] = Indica el nom dels grups.
*               in: operations[] = Indica el nombre d'operacions actives en cada un dels equips.
* @Retorn:      ----.
*
***********************************************************************/
void teamUpdate(char option, int team[], char name[], int operations[]){

    int i = 0;                        // Variable auxiliar índex.

    switch (option){

        // Opció 1: New fire
        case 'N':
            i = setIndex(name);
      
            // Output: El programa mostra un error en el cas que un equip no accepti més operacions.
            if (operations[i] == team[i]){
                
                printf("ERROR (Team %c: no member available) \n", name[i+1]);
                printf("\n");        
            }
            else{
                // Es redueix un bomber disponible.
                // team[i] = (team[i] - 1);
                // S'incrementa en el nombre d'operacions.
                operations[i] = (operations[i] + 1);

                // Output: Imprimeix quin és l'equip indicat per apagar el foc.
                printf("Operation assigned to team %c\n", name[0]);
                printf("\n");
            } 
            break;

        case 'E':
        // Opció 3: View Teams
            i = setIndex(name);

            // Output. S'intenta tancar una operació d'un equip, però no en té cap d’activa.
            if (0 == operations[i]){
                printf("\n");
                printf("ERROR (No operation to close) \n");
            }
            else{

                // Redueix el nombre d'operacions de l'equip.
                operations[i] = (operations[i] - 1);

                // Output. Indica el nombre d'operacions actives en l'equip.
                printf("\n");
                printf("Operation closed: %d active operations \n", operations[i]); 
            }
            break;
        default:
            break;
    }
}

/***********************************************************************
*
* @Finalitat:  Demana a l'usuari que anomeni un equip i impedeix que s'intrueixin valors incorrectes.
* @Paràmetres: in: name[] = Indica el nom dels grups. 
* @Retorn:     Retorna el caràcter corresponent a l'equip indicat per l'usuari.
*
***********************************************************************/
char enterTeam(char name[]){

    char team = ' ';
    char trash;            // Variable auxiliar per netejar el buffer

    // Output. Després d'executar l'operació “End fire” es mostren les operacions pendents.
    do{
        printf("Enter team: ");
        scanf("%c", &trash);
        scanf("%c", &team);

        // Passar minúscules a majúscules
        team = tinyToCapital(team);
    
    } while(('A' != team) && ('B' != team) && ('C' != team));

    name[0] = team;

    return(name[0]);
}

/***********************************************************************
*
* @Finalitat:   Incrementa la quantitat de bombers disponibles dins un equip.
* @Paràmetres:  in: name[] = Indica el nom dels grups. 
*               in: team[] = Indica el nombre de bombers disponibles en cada un dels equips.
* @Retorn:      ----.
*
***********************************************************************/
void expandTeam(int team[], char name[]){

    int i = 0;                        // Variable auxiliar índex.
    char aux = ' ';

    i = setIndex(name);
    aux = team[i];
    aux++;
    team[i] = aux;
}

/***********************************************************************
*
* @Finalitat:   Indica els bombers disponibles i les operacions en curs de cada un dels equips.
* @Paràmetres:  in: name[] = Indica el nom dels grups. 
*               in: team[] = Indica el nombre de bombers disponibles en cada un dels equips. 
*               in: operations[] = Indica el nombre d'operacions actives en cada un dels equips.
* @Retorn:     ----.
*
***********************************************************************/
void printSumary(char name[], int team[], int operations[]){

    int i = 0;

    for(i=0; i<MAXTEAMS; i++){
        printf("Team %c: %d members and %d active operations \n", name[i+1], team[i], operations[i]);
    }
}

int main(){
	
	// Declaració de variables locals
    char option = ' ';                                   // Opció seleccionada per l'usuari.
    float fire_distance = 0.0;                           // Distància del parc de bombers al foc.

    int team_fireman[MAXTEAMS];                          // Bomber disponible en cada equip
    char team_name[(MAXTEAMS + 1)];                      // Nom de l'equip (' ',A,B,C ...) El primer espai està reservat.
    int team_operations[MAXTEAMS];                       // Operacions en curs de cada equip.
    float fire_station[2];                               // Ubicació parc de bombers.

    /*** CODE ***/

    // Inicialitzar tots els arrays
    startArrays(team_fireman, team_name, team_operations);
    
	// Output. Donant la benvinguda.
    programStart(fire_station);
    
	do{
        // Output. Mostrant les opcions disponibles
        option = menu();

        switch (option){

        	// Opció 1: New fire
            case 'N':
            	printf("\n");

                //Output. Es demana la ubicació de l’incendi.
            	printf("Enter fire location: \n");
            	fire_distance = fireLocated(fire_station);
            	printf("\n");

                //Output. Es mostra quin és l'equip seleccionat.
            	teamSelection(team_name, fire_distance);

                // Output 3.2: S'actualitza la disponibilitat de l'equip.
                teamUpdate(option, team_fireman, team_name, team_operations);

                break;

            // Opció 2: End fire    
            case 'E':
                printf("\n");

                // Identificador de l'equip
                enterTeam(team_name);

                // S'actualitza la disponibilitat de l'equip.
                teamUpdate(option, team_fireman, team_name, team_operations);
                printf("\n");
                break;

            // Opció 3: View Teams
            case 'V':
                printf("\n");

                // Output. Es mostra la informació referent a cada equip.
                printSumary(team_name, team_fireman, team_operations);
                printf("\n");
                break;

            // Opció 4: Add member
            case 'A':
                printf("\n");
                
                // Identificador de l'equip
                enterTeam(team_name);
                printf("\n");

                // S'incrementa en un el màxim de bomber de l'equip.    
                expandTeam(team_fireman, team_name);
                break;

            default:
                break;
        }

    } while ('Q' != option);

    // Output. L'opció “Quit” finalitza l'execució del programa.
    printf("See you later! \n");


	return (0);
}