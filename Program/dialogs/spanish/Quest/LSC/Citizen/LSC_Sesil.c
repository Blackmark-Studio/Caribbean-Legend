// Сесил Галард - бабулька
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
				dialog.text = "No quiero hablar contigo. Atacas a civiles pacíficos sin razón alguna y los provocas para pelear. ¡Piérdete!";
				link.l1 = "Mm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "¿Deseas algo, joven?";
				link.l1 = TimeGreeting()+" Permíteme presentarme, "+GetFullName(pchar)+"Soy un recién llegado.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
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
			dialog.text = "¿A-ah, así que estás conociendo nuestra Isla y sus habitantes, verdad?";
			link.l1 = "Exactamente, ¿señora?..";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Halard. Cecille Halard.";
			link.l1 = "¡Encantado de conocerla, señora Halard! Es un placer.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "El mío también... ¿Y cómo llegaste aquí, joven? No recuerdo ningún naufragio reciente...";
			link.l1 = "Me trajeron aquí desde el continente en una barca... pero se hundió justo cerca de las costas de la Isla. Así es como me quedé sin barco.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "¿Un bergantín? Me cuesta creerlo... En este caso, tienes mucha suerte de haber navegado hasta la Isla en semejante cacharro y no haber caído en una tormenta. Las tormentas son eventos raros dentro de la isla, pero afuera son una amenaza, una amenaza muy repentina. \n¡Así que considérate afortunado y acostúmbrate a la forma de vida local! No quiero desanimarte, pero llegar aquí es fácil, mientras que dejar la Isla es casi imposible. No pienses que estoy refunfuñando, nadie ha logrado salir de la Isla con vida en los últimos diez años.";
			link.l1 = "Y aún así intentaré ser un poco más optimista. ¡Encantado de conocerte y verte por aquí!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "¿Sí, joven?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "¿Y cómo llegaste aquí, señora?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Has estado viviendo aquí por mucho tiempo, ¿no es así?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "¿Qué puedes decirme sobre los lugareños?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "¿Puedes contarme sobre personas interesantes que viven aquí?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sin preguntas. Perdón...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Fue hace tanto tiempo, por eso realmente no recuerdo cómo ocurrió. Naufragio y eso es todo...";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "A veces pienso que nací aquí... Pero, por supuesto, no es cierto. He vivido aquí toda la segunda mitad de mi vida. Y fue larga. Y moriré aquí porque no pienso dejar este lugar.";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Y no hay mucho que pueda decir, joven... todos son diferentes. Tenemos a todos aquí, blancos, negros, indios, ex esclavos y nobles, convictos del estado y soldados. Y antes había más de ellos. Cada uno tiene su propia historia y sus propias costumbres. A alguien no le importa pero alguien más todavía está ansioso por regresar. Así es como vivimos...";
			link.l1 = "Interesante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Las personas más interesantes aquí son: El mecánico-inventor de los Narvales, Herr Schmidt, armero de los Narvales, Sancho Carpentero, el cantinero nativo. Y ahora también tenemos al almirante con su segundo al mando.";
			link.l1 = "Lo consideraré...";
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
			link.l1 = "¡Muchacha insensata!";
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
			dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.","Sabes, correr con espada no se tolera aquí. Guárdala.","Escucha, no te hagas el caballero medieval corriendo con una espada. Guárdala, no te queda bien...");
			link.l1 = LinkRandPhrase("Bien.","Claro.","Como tú digas...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que guardes tu espada.","Escucha, soy ciudadano de la ciudad y te pediría que mantuvieras tu espada en su funda.");
				link.l1 = LinkRandPhrase("Bien.","Claro.","Como tú digas...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ten cuidado, camarada, al correr con un arma. Puedo ponerme nervioso...","No me gusta cuando los hombres caminan frente a mí con sus armas listas. Me asusta...");
				link.l1 = RandPhraseSimple("Entendido.","Lo estoy llevándome.");
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
