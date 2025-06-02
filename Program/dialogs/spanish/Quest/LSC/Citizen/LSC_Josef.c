// Джозеф Лодердэйл - английский военный офицер
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
				dialog.text = "No quiero hablar contigo. Atacas a civiles pacíficos sin razón y los provocas a pelear. ¡Lárgate! ";
				link.l1 = "Mm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Buen día, señor. Me alegra encontrar a un hombre noble aquí.";
				link.l1 = TimeGreeting()+" De hecho, he estado tan cerca de la gente común durante mi estancia en el Archipiélago que he comenzado a olvidar mi nobleza...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetFullName(pchar)+"¡Encantado de conocerte! ¿Qué dirás?";
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
			dialog.text = "¡Oh, y además eres modesto! ¡Un verdadero caballero! Creo que seremos amigos, no eres como ese pomposo Abad... Permíteme presentarme - Josef Loderdale, el antiguo capitán de la flota naval inglesa.";
			link.l1 = "Encantado de conocerte. "+GetFullName(pchar)+" a su servicio!";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Es bastante aburrido vivir aquí, así que visita la taberna por la noche, podemos tomar una copa de vino y tener una conversación interesante...";
			link.l1 = "Tendré eso en cuenta, señor. ¡Nos vemos!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha sucedido algo nuevo en la isla?","¿Me contarás los últimos chismes?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quiero hacerte unas preguntas sobre la isla.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sería un placer responder a sus preguntas, señor...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "¿Cómo llegaste aquí?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "¿Qué tipo de servicio puedo obtener aquí?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Siendo un oficial militar, ¿cuál es tu opinión sobre el dominio de los piratas aquí?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "He visto muchos cofres cerrados aquí, en la Isla. La gente no confía entre sí, ¿verdad?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sin preguntas. Perdón...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Haciendo mis deberes militares. Estaba luchando contra una balandra de guerra española, creíamos que era el barco responsable de saquear a los comerciantes ingleses. La pelea fue larga, casi los atrapamos, pero la tormenta repentina arruinó el juego. Como resultado, ambos barcos naufragaron cerca de los anillos exteriores. La fortuna tiene sentido del humor, yo y el capitán español sobrevivimos. Quizás ya lo hayas conocido aquí. Se llama Lorenzo Solderra, un pedazo raro de escoria. Ten cuidado con él.";
			link.l1 = "Entendido. Consideraré tu advertencia...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Si necesitas descansar, visita la taberna de Sancho. Siempre te proporcionará comida, bebidas y una cama. En caso de que quieras conseguir pólvora, municiones, armas y otras cosas, ve a Axel Yost, él es el dueño de la tienda. Medicinas pueden comprarse al hermano Julián, él también vende objetos sagrados en su iglesia\nLos Narvales tienen un herrero muy talentoso, llamado Schmidt. Dicen que fabrica excelentes espadas. También hay otro artesano talentoso entre los Narvales, pero no logré saber más sobre él\n Y si tienes problemas con piratas o clanes, entonces consulta a Giuseppe Fazio, él es el especialista adecuado para ese tipo de asuntos.";
			link.l1 = "¡Gracias por la información!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "No puedo decir que me guste, pero no hay nada que pueda hacer al respecto. Admito que solo tomó unos días para que los piratas hicieran las paces y establecieran el orden en la Isla. Antes de que llegaran los piratas, los clanes peleaban entre sí regularmente y la gente común sufría lo más\nAdemás, venden comida de manera muy ordenada y justa: los ciudadanos la obtienen por un precio muy bajo, no puedo decir lo mismo de los clanes, los piratas los desuellan vivos como venganza por iniciar una guerra\nConozco a un hombre muy inteligente entre los piratas, su nombre es Layton Dexter. Él es quien hace el comercio. Hablé con él una vez, me pregunto cómo un hombre tan talentoso y bien educado, que conoce tácticas, cartografía y comercio, se unió a los piratas\nLe tomó solo unos días para hacer un excelente mapa de la Isla. Lo vi, tiene casi todo. Creo que lo hizo para una posible guerra contra los clanes...";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Eso es lo correcto. Dicen que hace mucho tiempo, el robo era algo normal en la Isla hasta que todos los cofres obtuvieron nuevos cerrojos. Y sin embargo, todavía hay alguien que puede forzar los cofres. Aunque solo roba ron y joyas baratas, nunca tomó oro ni dinero.\nTodas las cerraduras son únicas, no existen llaves iguales - Jurgen Schmidt se aseguró de eso. Él fabrica no solo espadas, sino también cerraduras y llaves. Me dijeron que los cofres exteriores no contienen objetos de valor, los artículos serios siempre se guardan dentro de los barcos.";
			link.l1 = "Interesante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¿Qué estás haciendo ahí, eh? ¡Ladrón!","¡Solo mira eso! ¡Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre!","¿Has decidido registrar mis cofres? ¡No te saldrás con la tuya!");
			link.l1 = "¡Mierda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
			link.l1 = "¡Chica insensata!";
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
			dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.","Sabes, correr con la espada no se tolera aquí. Guárdala.","Escucha, no te hagas el caballero medieval corriendo con una espada por ahí. Guárdala, no te queda bien...");
			link.l1 = LinkRandPhrase("Bien.","Como desees...","Como dices...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.","Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.");
				link.l1 = LinkRandPhrase("Bien.","Como desees...","Como dices...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ten cuidado, camarada, al correr con un arma. Puedo ponerme nervioso...","No me gusta cuando los hombres caminan frente a mí con sus armas listas. Me asusta...");
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
