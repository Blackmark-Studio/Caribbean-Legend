// Вильям Патерсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "¿Hay algo que quieras?";
			link.l1 = "No, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "catoche":
			dialog.text = "Hola, sir. ¡Maldita sea, así que tú eres el que causó todo ese alboroto militar por aquí!";
			link.l1 = TimeGreeting()+", monsieur. Sí, fue mi barco el que realizó el desembarco. ¿Cuál es el problema de todas formas? ¿Quién eres tú? Un inglés, supongo?";
			link.l1.go = "catoche_1";
		break;
		
		case "catoche_1":
			dialog.text = "Un escocés, sir. Capitán de la Armada Inglesa William Paterson, y este es mi primer oficial y mano derecha, Archibald Calhoun. La cuestión es que hay un fuerte español en las junglas. Mi misión es echar a los malditos bastardos del fuerte, que han construido peligrosamente cerca del territorio inglés.\nRecientemente intentamos asaltarlo, pero los bastardos han logrado resistir a pesar de sus pérdidas. Partí en busca de refuerzos y...";
			link.l1 = "No hay necesidad de eso ahora. He completado tu asunto pendiente, el fuerte en la jungla está vacío. El comandante español Diego de Montoya está muerto, y su escuadrón ha sido aniquilado también.";
			link.l1.go = "catoche_2";
		break;
		
		case "catoche_2":
			dialog.text = "¿Qué clase de vigilantismo es este? ¿Cuál es tu motivación para emprender tal acción militar en territorio inglés?";
			link.l1 = "Me atrevo a recordarle, Capitán Paterson, que esto no es Belice. ¿Qué posesión inglesa? Todo este alboroto comenzó debido a Don Diego de Montoya, y su arriesgada decisión de atacarme a mí y a mis barcos.";
			link.l1.go = "catoche_3";
		break;
		
		case "catoche_3":
			dialog.text = "Ejem... ¿y qué razón tenía Don Diego para atacarlo, eh capitán?";
			link.l1 = "Él y yo tenemos una vieja enemistad... Desde el día en que el escuadrón que él lideraba atacó Saint-Pierre, y poco después fue eliminado con mi participación directa.";
			link.l1.go = "catoche_4";
		break;
		
		case "catoche_4":
			dialog.text = "¡Rayos y centellas! ¡Necesitaba a ese venerable caballero vivo! Iba a interrogarlo sobre por qué estableció una base militar en la jungla. No podía haber sido sin razón alguna...";
			link.l1 = "Lo siento, pero ahora no puede decirte nada. De todos modos, el fuerte puede contener soldados heridos de la guarnición. ¿Hay alguna posibilidad de que puedan hablar?";
			link.l1.go = "catoche_5";
		break;
		
		case "catoche_5":
			dialog.text = "Soldados... ¡Oh, de qué sirven unos testarudos cabezotas! ¿Dónde está el cadáver de Don Diego? ¡Podría haber tenido documentos importantes con él!";
			link.l1 = "Dejé a Don Diego en el suelo del fuerte de armas. Si lo necesitas tanto, puedes encontrarlo allí. No creo que pueda escaparse.";
			link.l1.go = "catoche_6";
		break;
		
		case "catoche_6":
			dialog.text = "Eh... ¿y quién te pidió que te entrometieras en los asuntos de los demás?... Me has causado bastante dolor de cabeza...";
			link.l1 = "Capitán, no entiendo por qué me reprende. He hecho su trabajo, he llevado a mi propia gente a la batalla, he arriesgado mi propia vida, y sin embargo, está descontento. Todo lo que tiene que hacer ahora es informar a Port Royal de su éxito en la misión y de todos sus asuntos. No reclamaré ningún crédito por su gloria, se lo aseguro.";
			link.l1.go = "catoche_7";
		break;
		
		case "catoche_7":
			dialog.text = "¿Reclamar el crédito? ¿Qué quieres decir con gloria? ¡No entiendes nada... Eh, está bien. Adiós, sir.";
			link.l1 = "¡Todo lo mejor para ti también!";
			link.l1.go = "catoche_8";
		break;
		
		case "catoche_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "GuardOT_OpenCatocheDoor", 10.0);
			sld = CharacterFromID("Archy");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 7.0);
			AddQuestRecord("Guardoftruth", "57");
		break;
		
		case "isladevieques":
			PlaySound("Voice\Spanish\sharlie\Willie Paterson.wav");
			dialog.text = "Hombre, los chismes no mienten que tienes nueve vidas como un gato. "+TimeGreeting()+", Sir de Maure. No pareces estar muy bien...";
			link.l1 = TimeGreeting()+", Sr. Paterson. Debo decir que usted y su amigo Archibald interpretaron sus papeles y me engañaron bastante bien, ¡malditos sean todos! Ni siquiera lo vi venir...";
			link.l1.go = "isladevieques_1";
		break;
		
		case "isladevieques_1":
			dialog.text = "Eh, no jures ante las puertas de la Tierra Santa. ¿No lo viste venir? Estoy halagado: he engañado a uno de los hombres más famosos del archipiélago. La idea del diario fue brillante, ¿no te parece?\nTenía que atraerte a algún lugar oscuro, matarte a campo abierto sería un escándalo, eres un amigo cercano de Philippe de Poincy, ¿me equivoco? Ahora vas a desaparecer sin dejar rastro y nadie sabrá nunca cómo.";
			link.l1 = "Entonces, ¿todo lo que me dijo Calhoun... era una mentira?";
			link.l1.go = "isladevieques_2";
		break;
		
		case "isladevieques_2":
			dialog.text = "No en absoluto. Realmente encontré al pobre Archibald en este lugar. Sin embargo, él no escribió ninguna memoria, el diario que encontraste en su habitación fue escrito a mi pedido especialmente para ti, Sir de Maure.\nHe estado vigilándote desde que nos conocimos en Cabo Catoche. ¿Fuiste tú quien tomó el mapa de las Dos Apariciones del cadáver de Don Diego? No lo niegues, sé que fuiste tú.";
			link.l1 = "¿También sabes sobre el Guardián de la Verdad?";
			link.l1.go = "isladevieques_3";
		break;
		
		case "isladevieques_3":
			dialog.text = "Esa es una pregunta estúpida. Por supuesto que sí. Y sé que también tienes la Garra del Jefe contigo. Y pronto devolverás esos objetos, que no te pertenecen.";
			link.l1 = "Me alegra que no tambalees como Don Diego. Aprecio la honestidad y la franqueza. Según entiendo, ¿tienes la brújula, la Flecha del Camino?";
			link.l1.go = "isladevieques_4";
		break;
		
		case "isladevieques_4":
			dialog.text = "¡Ja-ja! Bueno, seremos honestos hasta el final... ¿De verdad cree, sir, que soy tan idiota como usted y Don Diego, que llevaría conmigo un objeto tan preciado? La brújula está en Jamaica y ni siquiera en Port Royal, sino en un lugar donde nadie pensaría en buscar y bajo un seguro candado. Pero no necesitará esa información.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.OfficerKill"))
			{
				link.l1 = "Según entiendo, ¿ya me has dado por muerto, monsieur Paterson? ¡Me atrevo a proclamar que al gato le queda una vida más!.. ¿Dónde están mis oficiales?";
				link.l1.go = "isladevieques_5_1";
			}
			else
			{
				link.l1 = "Por lo que entiendo, ¿ya me has dado por muerto, monsieur Paterson? ¡Me atrevo a proclamar que al gato le queda una vida!..";
				link.l1.go = "isladevieques_5_2";
			}
		break;
		
		case "isladevieques_5_1":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.GirlKill"))
			{
				dialog.text = "¿Preocupado por tu dama, capitán? Tu mujer está tirada allí en los arbustos con un agujero en la frente. Ella ha trazado el camino para ti y pronto te unirás a ella. ¡Digo, qué chica tan bonita era! ¿Espero que la hayas disfrutado más de una vez?";
				link.l1 = "¡Eres un maldito infeliz! ¡Pagarás por eso, maldito enculado!";
				link.l1.go = "isladevieques_6";
			}
			else
			{
				dialog.text = "Sus oficiales han tendido el camino para usted, Sir de Maure. Están tendidos allí en los arbustos. Pronto se unirá a ellos.";
				link.l1 = "¡Eso ya lo veremos!";
				link.l1.go = "isladevieques_6";
			}
		break;
		
		case "isladevieques_5_2":
			dialog.text = "Nos aseguraremos de que realmente sea tu última.";
			link.l1 = "¡Ya lo veremos!";
			link.l1.go = "isladevieques_6";
		break;
		
		case "isladevieques_6":
			dialog.text = "Me haces reír. ¡Uno contra toda una tropa! De todos modos, basta de charlas... ¡Apunten sus mosquetes! ¡Fuego!";
			link.l1 = "...";
			link.l1.go = "isladevieques_7";
		break;
		
		case "isladevieques_7":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться patch-8
			LAi_ActorRunToLocation(npchar, "quest", "teleport", "IslaDeVieques_HouseEntrance", "quest", "mushketer", "GuardOT_WillyGetReady", 10.0);
			for(i=1; i<=5; i++)
			{
				sld = CharacterFromID("GuardOT_willymushketer_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
