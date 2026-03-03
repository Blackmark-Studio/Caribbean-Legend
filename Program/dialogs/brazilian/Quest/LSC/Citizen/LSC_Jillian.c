// Джиллиан Стайнер - просто девушка
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
				dialog.text = "Saia de perto de mim! Eu não falo com homens que arrumam briga na rua.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh... oi! Você me assustou. Não ouvi você chegando... Posso te ajudar?";
				link.l1 = TimeGreeting()+". Meu nome é "+GetFullName(pchar)+". Eu sou novo nesta ilha. Estou conhecendo os moradores e não resisti em vir falar com uma moça tão bonita. Qual é o seu nome?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Posso ajudar?";
				link.l1 = LinkRandPhrase("Jillian! Como você está? Alguma novidade?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está, madame. Até logo!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Você me faz corar, senhor, mas é um prazer. Obrigada pelo elogio. Meu nome é Jillian, Jillian Steiner.";
			link.l1 = "Um prazer mesmo, Jillian.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Você diz que é novo aqui? Me conte, como chegou até aqui? Sobreviveu a um naufrágio?";
			link.l1 = "Bem... algo assim. Naveguei até aqui em uma barca e quase consegui passar pelos recifes, mas infelizmente bati no anel externo e meu navio afundou. Só eu, de toda a tripulação, consegui nadar até aqui.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Oh! Então você veio atrás da ilha? Incrível!";
			link.l1 = "Sim, eu estava um pouco louco. Decidi encontrar a lendária Ilha da Justiça, e agora encontrei. Mas... não tenho certeza de como vou sair daqui.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "You are either very brave or very reckless. To sail here voluntarily... now you're stuck here with us; nobody has managed to leave this place in years.";
			link.l1 = "Eu ainda tenho esperança. Tudo bem, Jillian, obrigado, vou deixar você seguir com o seu dia. Até logo, madame!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sim, claro, "+pchar.name+". Estou ouvindo.";
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
				link.l3 = "E como você passa os seus dias?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Você diz que não é casada... Uma moça tão bonita não tem pretendentes?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Com licença...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Eu vim da Inglaterra com meus pais. Éramos pobres e queríamos recomeçar no Novo Mundo, mas... bem, meus pais morreram quando nosso navio foi pego por uma tempestade. Eu mal sobrevivi. Consegui chegar a um destroço no anel externo e fiquei lá inconsciente por um dia até que alguém me encontrou.\nComecei uma nova vida, mas talvez não aquela com que meus pais sonhavam.";
			link.l1 = "Me desculpe...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "E ir pra onde? Quem me aceitaria? Não tenho casa, nem marido, nem dinheiro. Nunca conheci outro lugar além dos becos de Londres... e desta ilha. Se meu destino é viver aqui, que seja – não é a pior coisa que poderia ter acontecido a uma mulher.";
			link.l1 = "Justo o suficiente, eu acho.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "I mostly help Brother Julian in the church. I also do some odd jobs in Axel's shop - that's how I make coin; I can't clamber around the shipwrecks at the outer ring.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Hi-hi... admiradores, sim, mas nenhum que preste. Não gosto de nenhum deles e não quero viver com um homem de quem não gosto. Os que eu gosto nem reparam em mim. Sou só uma garota pobre e comum...";
			link.l1 = "Tenho certeza de que você vai encontrar alguém, e ainda tem tanta vida pela frente...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ah, ladrão!","Tira essas mãos imundas daí, isso é meu!","Eu não te dei permissão para abrir meu baú!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Tire as mãos do meu peito, ladrão!";
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
			dialog.text = LinkRandPhrase("Senhor, por favor, guarde sua arma. Você está me assustando.","As pessoas aqui na ilha não gostam quando você anda por aí com uma espada.","Homens correndo por aí com espadas não me impressionam. Guarde isso.");
			link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você disser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"As pessoas aqui na ilha não gostam quando você anda por aí com uma espada.","Por favor, guarde sua espada, senhor. Homens armados correndo por aí nos deixam nervosos.");
				link.l1 = LinkRandPhrase("Tudo bem.","Me desculpe...","Desculpe, madame...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Senhor, por favor, guarde sua arma. Você está me assustando.","Homens correndo por aí com espadas não me impressionam. Guarde isso.");
				link.l1 = RandPhraseSimple("Desculpa...","Estou guardando isso.");
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
