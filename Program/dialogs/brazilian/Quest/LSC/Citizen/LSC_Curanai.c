// Куранай - индеец
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
				dialog.text = "Cara-pálida machucou irmãos e irmãs brancos. Não falo com você. Vá.";
				link.l1 = "Oh...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "O que o irmão branco quer?";
				link.l1 = TimeGreeting()+". 'Irmão branco'? Me diga, por que vocês índios nos chamam de irmãos brancos ou de cães de cara pálida, hein?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = ""+GetFullName(pchar)+"! "+TimeGreeting()+"! Quer alguma coisa?";
				link.l1 = LinkRandPhrase("Saudações, Curanai. O que tem acontecido na ilha ultimamente?","Aconteceu alguma novidade na ilha?","Vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				if (CheckAttribute(npchar, "quest.answer_2"))
				{
					link.l3 = "Mostre-me o que você conseguiu encontrar, talvez eu compre algo...";
					link.l3.go = "trade";
				}
				link.l5 = "Só queria saber como você está. Adeus!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Todos vivemos em paz aqui, irmão branco. Eu não chamo irmão branco de cachorro pálido. Nem todo pálido é cachorro, eu chamo muitos índios de 'cachorro de pele vermelha.'";
			link.l1 = "Você fala como um filósofo.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Eu não entendo você, irmão branco. O que significa 'filósofo'?";
			link.l1 = "Não importa, irmão de pele vermelha. Gosto do seu jeito de pensar. Meu nome é "+GetFullName(pchar)+". E o seu?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Curanai é meu nome. Fico feliz em saber o nome do irmão branco.";
			link.l1 = "Curanai... Bem, até mais!";
			link.l1.go = "exit";
			link.l3 = "Quero te fazer algumas perguntas sobre a ilha, Curanai.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 4)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Pergunte, irmão branco. Eu respondo.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Como você veio parar aqui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "O que você faz na ilha?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Você quer voltar para casa?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Você vive em paz na ilha? Acontecem brigas ou discussões por aqui?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Com licença...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Eu e sete guerreiros da minha tribo decidimos navegar até uma pequena ilha não muito longe da nossa, visível em dias claros. Construímos uma jangada de bambu e partimos. Mas uma tempestade nos pegou de surpresa e nos levou para o mar aberto. Não percebemos quão rápido nossa terra e ilha sumiram de vista.\nVagamos pelo mar por muitas, muitas noites e dias. Todos os meus irmãos morreram de sede e fome. Só eu sobrevivi — os espíritos tiveram piedade de mim e trouxeram a jangada até esta ilha.";
			link.l1 = "Entendo... que história triste.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "I fish; hit fish with harpoon. Rarely, rarely hit big crab. Then I happy; crab is tasty, very tasty. One crab enough for few days. And I also dive to bottom in one place, where no big crabs are. Pick yellow stone, blue stone, black stone, and pearl. Big and small. Then I sell them to white brother, white sister.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Eu quero voltar pra casa. Mas onde é casa? Não sei onde fica a vila nem como navegar até lá.";
			link.l1 = "Hum, me desculpe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Narwhal and Rivados tribes fight often, one against another. There are two chieftains; one hates the other. Someday, one kill the other. I see this. Rest of us live in peace and don't hurt anyone. Sometimes white brothers drink fire water and swear... but no killing. ";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Pare, cachorro de cara pálida! Não pegue o que não é seu!","Cara-pálida ladrão pega quando eu não vejo?! Não!","Essa mina é minha, cachorro de cara pálida! Não vou deixar você pegar o que não é seu!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "O quê?! Veio saquear meus baús? Você não vai sair impune!";
			link.l1 = "Garota tola!";
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
			dialog.text = LinkRandPhrase("Não gosto de ver o aço nu do irmão branco. Guarde isso.","Irmãos e irmãs brancos não gostam de ver você andando com aço. Pare, irmão.","Não banque o herói, irmão branco. Guarde sua lâmina.");
			link.l1 = LinkRandPhrase("Tudo bem.","Claro.","Desculpa...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Eu vivo aqui em paz. Não é certo andar com arma na mão.","Espere, irmão branco. Guarde o aço, isso me assusta.");
				link.l1 = LinkRandPhrase("Tudo bem.","Tanto faz então.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Irmão branco, guarde a lâmina. Isso me deixa nervoso...","Homem branco só pega aço se pretende usar. Guarde isso...");
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
