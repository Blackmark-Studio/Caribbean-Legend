// Оеларт Котеел - канонир
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
				dialog.text = "Fora da minha vista, senhor. Não tenho nada a dizer para homens que atacam pessoas inocentes.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bom dia, senhor! O que acha deste tempo?";
				link.l1 = TimeGreeting()+". Eu gosto de qualquer tempo, menos tempestades em alto-mar...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Quer alguma coisa?";
				link.l1 = LinkRandPhrase("Bom dia, senhor. Quais são as novidades?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está. Tenha um bom dia, senhor!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ha-ha! Eu sinto o mesmo. Nunca te vi antes... meu nome é Oelart Koteel. Eu era capitão de canhão em um navio de guerra holandês.";
			link.l1 = ""+GetFullName(pchar)+". Eu sou novo aqui, acabei de chegar.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Também sou novo aqui, estou há menos de um ano — e espero de verdade não ter que ficar muito mais tempo, embora todo mundo tente me convencer do contrário. Prazer em te conhecer!";
			link.l1 = "Prazer em te conhecer também, "+npchar.name+"...";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Bom dia, senhor. Quais são as novidades?","Aconteceu alguma novidade na ilha?","Vai me contar as últimas fofocas?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quero te fazer algumas perguntas sobre a ilha.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Estou ouvindo.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Como você veio parar aqui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Você quer deixar a ilha?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Você faz ideia de como a ilha se formou?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Você já visitou os navios dos clãs?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Perdão...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "É uma história bem comum. Lutamos contra uma escuna inglesa e quase vencemos. Eles fugiram, nós perseguimos. Passou um dia, estávamos prestes a alcançá-los, mas eles derrubaram nosso mastro principal e conseguiram escapar.\nDepois, quase afundamos numa forte tempestade, fomos pegos por uma correnteza e, no fim, nosso navio foi lançado contra um recife perto do anel externo. Pouquíssimos conseguiram sobreviver...";
			link.l1 = "Triste...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Esse é o meu sonho. Você não faz ideia do quanto estou entediado deste lugar. Mas como sair daqui? Não faço a menor ideia.\nNão há navios flutuando por aqui e não existe chance de construir um novo – e seria suicídio tentar sair em um bote pequeno. As tempestades destruiriam qualquer coisa tão frágil.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "O naufrágio mais antigo que vi na ilha tem cerca de cem anos, mas é bem possível que a ilha seja muito mais velha, por causa do anel externo. Ele é feito de navios do topo até o fundo — podem existir embarcações realmente antigas nas profundezas, a alguns metros da vista.\nQuanto à formação da ilha... Acredito que as correntes e tempestades trazem navios à deriva para cá, então um banco artificial foi criado. O anel externo foi construído sobre ele.\nOs navios internos onde vivemos... ou foram os primeiros de todos, ou de alguma forma conseguiram atravessar o anel externo. É bem possível, afinal o Almirante e seus piratas chegaram até nós em sua chalupa.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Eu já estive com o Protetor e o Velasco, no território dos Rivados. O Black Eddy certa vez precisou de uma consulta sobre os canhões do navio — não me pergunte por quê, ele nunca explicou. Então um dos rivados me encontrou e me passou a senha.\nOs guardas são duros, então nem pense em tentar passar por eles sem a senha.";
			link.l1 = "Vou me lembrar disso.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Senhor, o que você está... Ah! Você está me roubando! Pare!","Mal acabo de virar as costas, você tenta me roubar?! Como ousa!","Tire as mãos do meu baú do mar, ladrão!");
			link.l1 = "Merda...";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "O quê?! Resolveu saquear meu baú? Você não vai sair impune dessa!";
			link.l1 = "Vadia!";
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
			dialog.text = LinkRandPhrase("Mynheer, por favor, guarde sua arma. Você está me deixando nervoso.","Não saia correndo por aí com uma lâmina, você pode acabar se machucando.","Correr por aí com uma espada entre pessoas inocentes não é tão nobre quanto você pensa, senhor. Guarde isso.");
			link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você disser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Mynheer, por favor, guarde sua arma. Você está me deixando nervoso.","Não saia correndo por aí com uma lâmina, você pode acabar se machucando.");
				link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Mynheer, por favor, guarde sua arma. Você está me deixando nervoso.","Não saia correndo por aí com uma lâmina, você pode acabar se machucando.");
				link.l1 = RandPhraseSimple("Desculpe.","Estou guardando isso.");
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
