// Антонио Бетанкур - потомок Франциско Бетанкура
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "No quiero hablar contigo. Atacas a civiles pacíficos sin razón y los provocas a pelear. ¡Lárgate!";
				link.l1 = "Mm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hola, Hola... ¿Qué quieres, amigo?";
				link.l1 = TimeGreeting()+". Mi nombre es "+GetFullName(pchar)+" Y solo quería saber quién eres. Mira, acabo de llegar, caminando por la ciudad y hablando con la gente.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "¡Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+". ¿Qué quieres esta vez?";
				if(CheckAttribute(pchar, "questTemp.LSC.Betancur"))
				{
					link.l4 = "Antonio, dicen que conoces bien la historia de la Isla. Tengo una pregunta para ti sobre ella.";
					link.l4.go = "dolly";
				}
				dialog.text = "¡Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+". ¿Quieres algo?";
				link.l1 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha ocurrido algo nuevo en la isla?","¿Me contarás los últimos chismes?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quiero hacerte unas preguntas sobre la isla.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Solo quería saber cómo estás. ¡Nos vemos!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Espléndido. Y te irá bien, porque todos somos una gran familia aquí. Excepto por los Narvales y los sucios Rivados, por supuesto. Mi nombre es Antonio, Antonio Betancourt. Soy el nieto de Francisco Betancourt por si este nombre te dice algo.";
			link.l1 = "¿Francisco Betancourt? He oído este nombre antes... ¡Ah, claro! Dios me habló de él y leí sobre él en las notas de Alvarado...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "No tengo idea de quién es ese Dios tuyo, pero el capitán Alvarado nos visitó hace mucho tiempo. Lo vi personalmente cuando era niño. Zarpó de la isla y escribió sobre ello en sus manuscritos. Y Francisco Betancourt era un almirante español, un comandante de escuadrón militar. Él comenzó la historia de este lugar debido al hecho de que todos los Rivados son descendientes de esclavos negros del Tartarus, el buque insignia del escuadrón. Los Narvales son hijos de los primeros colonos blancos, miembros de la tripulación del Tartarus, San Agustín y San Jerónimo.";
			link.l1 = "¡Increíble! ¿Entonces naciste aquí?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Exactamente. Soy un descendiente directo de un hombre que básicamente ocupó la Isla.";
			link.l1 = "Ya veo. Encantado de conocerte, Antonio. Nos vemos.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестовая часть
		case "dolly":
			dialog.text = "Hm... Claro, amigo, pregúntame. Responderé tus preguntas, por supuesto, pero solo si conozco las respuestas.";
			link.l1 = "Dime, ¿recuerdas el tiempo cuando el galeón San Geronimo todavía estaba aquí?";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Claro que sí. Era un barco muy especial. Había una estatua india interesante y esos paganos inmundos, los Rivados, estaban realizando sacrificios.";
			link.l1 = "¿Y cómo lo estaban haciendo? ¿Se estaban llevando los corazones de las personas como los mayas? ¿O estaban cortando cabezas?";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = "No... Era una estatua muy especial - arrastraba a las víctimas hacia sí misma y desaparecían para siempre. La herramienta del diablo... Gracias a Dios se ha hundido con el barco y nunca causará daño. Es bastante interesante que los sacrificios siempre se hacían a la misma hora por la mañana. La estatua solía volverse de oro bajo la luz del sol naciente\nFue entonces cuando los salvajes traían víctimas, principalmente los Narvales que capturaban.";
			link.l1 = "¡Interesante! ¿Y alguien alguna vez ha intentado explorar cómo funciona la estatua?";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "¡Por supuesto que no! Primero, los Rivados no permiten que nadie excepto los suyos se acerque a San Gerónimo y, en segundo lugar, un católico honesto debe mantenerse alejado de las acciones del diablo.";
			link.l1 = "Entendido. Veo que no te gustan los Rivados. ¿Estoy en lo cierto?";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "¿Lo hago? ¡Odio a esos sucios paganos! Por si no lo sabes, mi abuelo era el capitán del barco donde los Negros con su líder Rivados se amotinaron. Dejar a su llamado líder pudrirse dentro de la bodega fue lo correcto. También tenía una hermosa llave del tesoro de Santa Ana. Nadie sabe dónde encontrar el tesoro, tal vez esté en el fondo del mar rodeado de cangrejos, pero la llave era un dulce recuerdo para mí y aun así fue robada. Estoy seguro de que los negros lo hicieron. Deben estar intentando encontrar el tesoro. Dudo que lo logren, ha pasado demasiado tiempo, ¡ja, ja! Escoria...";
			link.l1 = "Ya veo. ¡Gracias por tu interesante historia!";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "¡De nada, siempre estoy encantado de hablar!";
			link.l1 = "¡Adiós!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Betancur");
			AddQuestRecord("LSC", "16");
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Estoy escuchando, amigo.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "¿Entonces no has visto nada más que la Isla en tu vida?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Eres nacido aquí... ¿Y por qué no eres miembro del clan Narval? Pensé que todos los nativos blancos eran Narvales...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "¿Y qué haces en la Isla?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Dime, ¿alguna vez has querido dejar la Isla por un tiempo? Para ver el mundo...";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No hay preguntas. Perdón...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Parece que sí,  así es. Pero no pienses que soy un idiota o de mente estrecha. He heredado una fina biblioteca de mi abuelo y mi padre me proporcionó una excelente educación. Conozco la historia antigua, geografía, astronomía, sé inglés, francés, español e incluso latín. Muchos marineros que han estado en todas partes saben menos que yo. Aunque no he visto nada excepto estos naufragios, mentalmente he visitado Europa, China e India...";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "No es cierto, aunque tienes razón en un noventa por ciento. Pero no soy un Narval y no quiero convertirme en uno de ellos. ¿Para qué propósito? ¿Para hacer guardia durante horas como un tonto o para luchar con los Rivaos? Ni en sueños, eso déjamelo a mí. Soy diferente. Prefiero vivir independientemente y leer libros.";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Padre me dejó una herencia decente y la gasto con cuidado. Así que no necesito merodear por los naufragios para encontrar algunas joyas para intercambiar por comida. No creo en grandes tesoros dentro de barcos viejos\nEl único tesoro que conozco es el tesoro de Santa Ana. Es un gran cofre de hierro. Pero nadie ha logrado encontrarlo aún\nAdemás, voy a escribir una historia detallada de la Isla basada en historias locales. ¿Qué piensas - debería intentarlo?";
			link.l1 = "Estoy seguro de ello. Conozco al menos a un hombre en el Archipiélago que pagaría por tal libro mucho oro. Así que es tu oportunidad...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "A veces pienso en ello. Tal vez si un barco que pudiera manejar la corriente y sobrevivir a las tormentas llegara aquí, me arriesgaría. ¡Tengo muchas ganas de ver cosas que se describen tan interesantemente en mis libros! Pero estos son solo sueños por ahora...";
			link.l1 = "Los sueños se hacen realidad. Solo cree en ellos...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¿Qué estás haciendo ahí, eh? ¡Ladrón!","¡Solo mira eso! En cuanto me perdí en la contemplación, ¡decidiste revisar mi cofre!","¿Has decidido revisar mis cofres? ¡No te saldrás con la tuya!");
			link.l1 = "¡Mierda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
			link.l1 = "¡Chiquilla necia!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.","Sabes, correr con una hoja no se tolera aquí. Guárdala.","Escucha, no juegues a ser un caballero medieval corriendo con una espada. Guárdala, no te queda bien...");
			link.l1 = LinkRandPhrase("Bien.","Como desees...","Como dices...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que mantengas tu espada guardada.","Escucha, soy ciudadano de la ciudad y te pediría que guardes tu espada.");
				link.l1 = LinkRandPhrase("Bien.","Como desees...","Como dices...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ten cuidado, compañero, al correr con un arma. Puedo ponerme nervioso...","No me gusta cuando los hombres caminan frente a mí con sus armas listas. Me asusta...");
				link.l1 = RandPhraseSimple("Entendido.","Me lo estoy llevando.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
