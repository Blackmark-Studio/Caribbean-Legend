// Орели Бертин - просто жительница
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
				dialog.text = "No quiero hablar contigo. Atacas a civiles pacíficos sin razones y los provocas a pelear. ¡Piérdete!";
				link.l1 = "Mm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Buen día, señor. ¿Qué dirás?";
				link.l1 = TimeGreeting()+". Mi nombre es "+GetFullName(pchar)+", soy un novato aquí, así que estoy conociendo a los lugareños.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "¡Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+". ¿Quieres algo?";
				link.l1 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha sucedido algo nuevo en la isla?","¿Me contarás los últimos chismes?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quiero hacerte algunas preguntas sobre la isla.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Solo quería saber cómo estás. ¡Nos vemos!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ya veo. Me llamo Orelie Bertine. ¿Cómo llegaste aquí?";
			link.l1 = "Digamos que solo quería ver la mística Isla Justicia.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Así que debes ser uno de esos locos que vienen aquí por su propia voluntad... Bueno, ahora tendrás suficiente tiempo para ver la Isla y comer bastante de su 'justicia'.";
			link.l1 = "¿Y hay algún problema con la justicia según tu sarcasmo?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "No, todo está bien. Pero por alguna razón tenemos que pagar a los piratas por nuestra comida, que solía ser gratuita para todos no hace mucho. Y cuando los clanes comienzan a pelear en nuestra parte de la Isla, se supone que debemos quedarnos dentro de los barcos para evitar ser disparados o masacrados. Quiero decir que se les permite hacer lo que quieran en nuestro territorio, pero nosotros no podemos hacer lo mismo en el de ellos. Pero está bien, no más problemas...";
			link.l1 = "Ya veo. Bien, me alegra conocerte. ¡Nos vemos!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Estoy escuchando.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "¿Has estado viviendo aquí por mucho tiempo?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "¿Hay algo interesante en la Isla?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "¿Qué opinas de los clanes?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "¿Los piratas te están molestando?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sin preguntas. Perdón...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Por mucho tiempo. Ya he perdido la cuenta. Deben ser diecisiete años... no, quizás dieciocho... ¿o son veinte? ¿Cuál es el año actual?";
			link.l1 = "Veo... ¿Entonces eres un veterano aquí?";
			link.l1.go = "ansewer_1_1";
		break;
		
		case "ansewer_1_1":
			dialog.text = "Relativamente. Todavía recuerdo tiempos cuando los bucaneros comerciaban con nosotros y los Narvales más temerarios e inteligentes navegaban hacia el continente para intercambiar provisiones por mercancías de las bodegas de los barcos. Pero hay mucha gente que nunca ha visto otros lugares, solo la Isla, porque nacieron aquí. No son solo veteranos aquí, sino nativos.";
			link.l1 = "Interesante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Sí, lo es. Todo aquí es interesante. Pasea y compruébalo por ti mismo. Nada alrededor de la parte central de la Isla. Visita una taberna, una tienda y una iglesia. El problema es que el interés caerá en una semana, te lo puedo asegurar.";
			link.l1 = "Entendido...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "¿Y cómo se supone que debemos pensar sobre esos bandidos? Estoy tratando de mantenerme alejado de ellos, eso es todo. Al menos los Narvales hacen algún bien a la Isla, tienen artesanos muy talentosos entre ellos, pero los Rivaos son solo salvajes y paganos. \nTodavía viven según sus leyes africanas como hace cientos de años. Animales. Lo único que han aprendido es a usar armas de fuego. ¡Dicen que cometen rituales de canibalismo!";
			link.l1 = "Tal pesadilla...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "La parte donde nos venden nuestra propia comida es un poco molesta, pero no hacen daño a los ciudadanos. En realidad, al contrario, pusieron a los clanes en orden y previenen cualquier violencia\nHubo un ciudadano que estaba causando problemas y blandía su sable. Incluso hirió a otros dos locales. Los piratas lo llevaron al Tártaro por unas semanas. Ahora el hombre está tranquilo y pacífico. No lo vemos a menudo, el anillo exterior es su nuevo hogar...";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¿Qué haces ahí, eh? ¡Ladrón!","¡Mira eso! Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre.","¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
			link.l1 = "¡Maldita sea!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
			link.l1 = "¡Muchacha tonta!";
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
			dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.","Sabes, correr con espada no se tolera aquí. Quítala de en medio.","Escucha, no juegues al caballero medieval corriendo con una espada. Guárdala, no te queda bien...");
			link.l1 = LinkRandPhrase("Bien.","Bien.","Como dices...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que bajaras tu espada.","Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.");
				link.l1 = LinkRandPhrase("Bien.","Bien.","Como dices...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ten cuidado, amigo, al correr con un arma. Me puedo poner nervioso...","No me gusta cuando los hombres caminan frente a mí con sus armas listas. Me asusta...");
				link.l1 = RandPhraseSimple("Entendido.","Lo estoy llevando.");
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
