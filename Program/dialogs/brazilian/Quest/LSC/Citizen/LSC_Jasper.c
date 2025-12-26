// Джаспер Пратт - каторжник
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
				dialog.text = "Me deixe em paz, senhor. Eu não falo com quem faz mal aos inocentes! Você é mais criminoso do que eu!";
				link.l1 = "Eu estou...?";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bom dia, senhor. Precisa de alguma coisa?";
				link.l1 = TimeGreeting()+". Meu nome é "+GetFullName(pchar)+". Eu sou novo aqui. Posso perguntar seu nome?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Quer alguma coisa?";
				link.l1 = LinkRandPhrase("Olá, Jasper. Ouviu alguma novidade ultimamente?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está. Até outra hora, Jasper!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Eu? Sou Jasper Pratt. Talvez já tenha ouvido me chamarem de condenado do estado – por isso todos me olham torto. Ah, que se danem. Eu sou o que sou...";
			link.l1 = "Não me importa quem você foi, me importa quem você é.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Pena que nem todos pensam como você, senhor.";
			link.l1 = "Bem, sou conhecido pela minha atitude liberal...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Bom pra você. Não se preocupe. Apesar do meu passado, não sou ameaça pros bolsos nem pros baús dos habitantes da Ilha. Fico feliz de finalmente poder viver em paz.";
			link.l1 = "Prazer em te conhecer, Jasper. Até a próxima!"link.l1.go ="exit";
			link.l2 = LinkRandPhrase("Oi Jasper. Ouviu alguma novidade ultimamente?","Aconteceu alguma novidade na ilha?","Vai me contar as últimas fofocas?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quero te fazer algumas perguntas sobre a ilha.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Vou responder se eu puder. Pergunte.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Como você veio parar na ilha?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Você gosta deste lugar?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Você disse que as pessoas te olham de lado. É por causa do seu passado?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Esta ilha é bem interessante, não acha?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Perdão...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Fugi de uma plantação em Cuba. Éramos cinco e decidimos que morrer era melhor do que quebrar as costas ou apanhar todo dia. Conseguimos enganar os guardas e sumir na mata. Quando chegamos à praia, construímos uma jangada.\nTentamos chegar a Tortuga, mas ninguém sabia navegar, então nos perdemos. Depois a água acabou... Não gosto nem de lembrar disso. Enfim, fui o único que conseguiu chegar à ilha e sobreviver.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Sabe, eu gosto daqui. Depois de tudo que passei na plantação, este lugar parece o paraíso na Terra. Não preciso de muito... um pouco de comida, água, um copo de rum à noite – e ninguém aqui quer me açoitar com um chicote. Só isso já é motivo suficiente pra ficar. Vou ficar feliz em morrer aqui quando chegar minha hora.";
			link.l1 = "Acho que sim...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "O negócio é o seguinte, essa ilha virou um parque de diversões pra um ladrão. Ele aparece de noite, tranca nenhuma segura o sujeito. Quase sempre ele saqueia perto dos aposentos do Almirante, onde ficam os piratas, todo mundo já teve seus baús revirados uma hora ou outra.\nNinguém sabe quem é o ladrão, então desconfiam logo de quem tem... hã... passado criminoso.\nSó que esse ladrão é meio esquisito: ele só leva garrafas de bebida e umas bugigangas — nada realmente valioso. Engraçado, né?";
			link.l1 = "É, engraçado...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "'Tis. Swam a lot 'round the inner ships o' th'island. Not many exits from the water: San Augustine, on the canted deck either side o' the rope bridge; Gloria, up the fallen mast...\nIf'n you swim close to the Phoenix and then 'round the Ceres you can reach Mary Casper's cabin through the ship's bow.\nThe hole in Tartarus's belly will lead you to the prison. There's a hole in the San Augustine's bow what opens into th'Admiral's storage room, but don't go in there - the guards'll cut you down; remember, the lowest door of Tartarus is locked for a reason.\nAn' o' course you can get aboard the Fernanda, the lone fluyt. They say no one lives there but I've often seen lights inside the cabin, and sometimes I can hear drinking songs... and a man cryin' out, in pain or grief.";
			link.l1 = "Interessante... tanta coisa para explorar.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ah! Ali está o ladrão! Ele está bem ali!","E dizem que eu sou o criminoso?! Tira as mãos, moço!","Encontrei o ladrão! Ele está aqui! Ele está aqui!");
			link.l1 = "Espere, não!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Tira seus dedos do meu peito! Socorro!";
			link.l1 = "Porra!";
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
			dialog.text = LinkRandPhrase("Moço, pelo amor de Deus, guarde essa lâmina! Você está assustando o pessoal.","É melhor não deixar ninguém te ver balançando isso por aí... você vai acabar no Tártaro.","Não precisa ficar brandindo uma lâmina por aqui. Você está entre amigos.");
			link.l1 = LinkRandPhrase("Tudo bem.","Desculpe.","Tudo bem...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escuta, senhor, guarda isso. Não precisa de espada por aqui.","Esta é minha casa, e aqui é seguro porque ninguém fica por aí balançando espada. Guarde isso.");
				link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem, então.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Moço, pelo amor de Deus, guarde essa lâmina! Você está assustando o pessoal.","Esta é minha casa, e aqui é seguro porque ninguém fica por aí balançando espada. Guarde isso.");
				link.l1 = RandPhraseSimple("Entendi.","Eu vou levar isso.");
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
