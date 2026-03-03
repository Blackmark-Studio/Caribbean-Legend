// Лайонел Маскетт - мещанин
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
				dialog.text = "Não quero falar com você. Você ataca pessoas pacíficas sem motivo e ainda provoca para brigar. Vai embora!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Saudações, "+GetAddress_Form(NPChar)+". Você é novo aqui?";
				link.l1 = TimeGreeting()+". Meu nome é "+GetFullName(pchar)+" - e sim, sou eu.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = ""+GetFullName(pchar)+", "+TimeGreeting()+". Quer alguma coisa?";
				link.l1 = LinkRandPhrase("Tem alguma coisa interessante pra me contar?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está. Adeus.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Meu nome é Lionell. Prazer em te conhecer. Como você veio parar aqui?";
			link.l1 = "Vim numa barca... Ouvi dizer que havia uma enseada de contrabandistas por aqui e decidi procurar... Bem, minha barca afundou e cá estou eu.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "As pessoas realmente acham que a ilha é um esconderijo de contrabandistas?";
			link.l1 = "Não oficialmente. A maioria das pessoas nem acredita que você existe.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "E por que fariam isso? Não estamos em nenhum mapa. Você não pode sair daqui. Os moradores dizem que a ilha já fez comércio com Cuba, mas eu não me lembro disso e já moro aqui há quase oito anos.";
			link.l1 = "Entendi. Foi um prazer conversar com você. Adeus.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Tem alguma coisa interessante pra me contar?","Aconteceu alguma novidade na ilha?","Vai me contar as últimas fofocas?");
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
				link.l2 = "Você gostaria de sair e ir para o Continente?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "O que as pessoas fazem aqui, na ilha?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Onde se consegue as coisas aqui? Comida, roupas, bebidas?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Com licença...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "That is an odd story. This island is the only place I've known in the Caribbean. I had a run of hard luck in England so I booked passage on a merchantman to the New World. I was going to find a job in Belize - maybe as a clerk for the harbourmaster. But we never made it to Belize.\nI'm no sailor, so I don't know the details, but a storm cropped up and wrecked us on the reefs. I'll never forget that terrible blow... the screaming...\nSomeone shouted, 'She's holed!' and people started jumping overboard. Me... I can't swim, so I stayed. Ironically, that saved my life: the ship survived and the storm broke at dawn.\nBefore I left the ship I took some food, built a raft, and paddled over a tranquil sea to the outer ring. That's how I survived; the only one out of the whole crew.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Esse era o meu sonho nos primeiros dois anos aqui, mas agora... Será que a ilha é mesmo pior do que qualquer outro lugar? Não há campos verdes nem árvores, mas existe um mar magnífico e um céu noturno repleto de estrelas. Estou bem alimentado, visto roupas decentes – melhores do que eu poderia pagar vivendo na Inglaterra. Tenho muitos amigos...\nNão, senhor, não quero sair daqui. O que me espera lá fora? Um emprego de escritório sob as ordens de um chefe rabugento por trezentos pesos por semana? De jeito nenhum! Encontrei tudo o que procurava bem aqui. Não preciso de mais nada.";
			link.l1 = "Entendi. Fico feliz por você!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "O que quiserem. Os Narvais e os Rivados vivem em guerra. Os piratas vendem mantimentos. Axel Yost compra e vende sucata. Sancho Carpentero serve bebidas e anima o povo. Irmão Julian reza, celebra missa e vende remédios. Lauderdale e Solderra tramam um contra o outro. O Abade gosta de se exibir ao sol. Jillian e Tanneke sonham com o amor verdadeiro...";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Dos destroços, meu amigo, dos destroços. Resgatar o que sobrou dos navios quebrados no anel externo é o passatempo favorito de muitos aqui na ilha. Você encontra de tudo lá: armas, remédios, especiarias e rum. Muitos dos destroços ainda não foram explorados — as correntes trazem novas vítimas o tempo todo...";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Tire as mãos das minhas coisas, ladrão!","Viro as costas por um minuto e você tenta me roubar?! Eu vou te mostrar!","Revirando meus baús?! Você não vai sair impune dessa!");
			link.l1 = "Cale a boca!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Como você ousa mexer nas minhas coisas sem permissão! Socorro! Ladrão!";
			link.l1 = "Cale a boca!";
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
			dialog.text = LinkRandPhrase("Guarde sua arma, amigo. Isso me deixa nervoso.","Sabe, andar por aí com uma lâmina na mão não é permitido aqui. Guarde isso.","Escuta, não banque o cavaleiro branco, correndo por aí com uma espada. Isso não combina com você, guarda isso...");
			link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você disser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escute, eu sou um cidadão desta ilha e gostaria que você abaixasse sua espada.","Escute, eu sou um cidadão desta ilha e gostaria que você baixasse sua espada.");
				link.l1 = LinkRandPhrase("Tudo bem.","Certo.","Como você diz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Cuidado, amigo. Andar por aí com uma arma... me deixa nervoso.","Eu não gosto de homens andando por aí com a arma na mão. Isso me assusta.");
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
