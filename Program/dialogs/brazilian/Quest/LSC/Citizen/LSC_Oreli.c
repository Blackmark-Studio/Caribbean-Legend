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
				dialog.text = "Me deixe em paz, senhor. Você machucou alguém! Vá embora!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bom dia, senhor.";
				link.l1 = TimeGreeting()+". Meu nome é "+GetFullName(pchar)+", sou novo por aqui, então estou conhecendo os moradores.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Quer alguma coisa?";
				link.l1 = LinkRandPhrase("Bom dia, Madame Bertine. Quais são as novidades na ilha?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está. Até mais!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Entendi. Meu nome é Orelie Bertine. Como você veio parar aqui?";
			link.l1 = "Digamos apenas que eu queria ver a lendária Ilha da Justiça.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Então você deve ser um desses malucos que vêm aqui por vontade própria... Bem, agora vai ter tempo de sobra pra conhecer a ilha e experimentar bastante da tal 'justiça' dela.";
			link.l1 = "Pelo seu sarcasmo, você vê algum problema com o tipo de justiça deles?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Não, está tudo bem – mas, por algum motivo, agora temos que pagar aos piratas pela comida, que até pouco tempo atrás era de graça para todos. E quando os clãs trazem suas brigas para o nosso lado da Ilha, a gente tem que ficar trancado nos navios para não levar tiro ou facada. Quero dizer, eles podem fazer o que quiserem no nosso território, mas a gente não pode fazer o mesmo no deles. Mas tudo bem, não tenho problema nenhum... nenhum mesmo...";
			link.l1 = "Entendo... Bem, fico feliz por ter conhecido você. Até logo, Madame Bertine!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Fale logo, agora.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Você já mora aqui há muito tempo?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Tem alguma coisa interessante na ilha?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "O que você acha dos clãs?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Os piratas te incomodam?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Perdão...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Faz muito tempo. Já perdi a conta dos anos... deve fazer uns dezessete... não, talvez dezoito... ou seriam vinte? Qual é a data de hoje?";
			link.l1 = "Então você é um veterano?";
			link.l1.go = "ansewer_1_1";
		break;
		
		case "ansewer_1_1":
			dialog.text = "Veja bem: ainda me lembro da época em que os bucaneiros de Cuba faziam trocas conosco, e os Narvais mais astutos e ousados navegavam até o continente para buscar comida em troca de mercadorias resgatadas dos porões dos navios.\nMas agora há muita gente que nunca conheceu outro lugar além da ilha, porque nasceu aqui. Eles não são apenas antigos moradores, mas nativos.";
			link.l1 = "Interessante!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Claro. A ilha é um lugar interessante. Dê uma volta, veja por si mesmo, nade entre os destroços, visite a taverna, a loja e a igreja. Mas te garanto que a novidade passa em uma semana.";
			link.l1 = "Tudo bem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "O que você quer que eu diga? Eu tento evitá-los. Pelo menos os Narvais fazem algum bem para a ilha – têm artesãos muito talentosos entre eles – mas os Rivados são apenas selvagens e pagãos.\nVivem segundo suas leis africanas, como os ancestrais deles faziam há centenas de anos. Animais. A única coisa que aprenderam foi a usar armas de fogo. Tem gente que diz que os Rivados cometem atos rituais de canibalismo!";
			link.l1 = "Que pesadelo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "A parte em que eles vendem nossa própria comida me incomoda, mas nunca fazem mal aos cidadãos. Pelo contrário, eles colocaram os clãs na linha e acabaram com as guerras constantes.\nTeve uma vez, um cidadão que causava problemas para todo mundo – gostava de ficar desfilando com a espada. Feriu dois moradores. Os piratas o trancaram no Tártaro por algumas semanas, e agora o homem está bem mais calmo. Não vemos ele com frequência – o anel externo virou a nova casa dele...";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("O que você pensa que está fazendo, ladrão?!","No minuto em que viro as costas, você saqueia meu baú?!","Revistando meu baú, hein? Você não vai sair impune disso!");
			link.l1 = "Droga!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Seu ladrão! Você vai apodrecer no Tártaro por isso!";
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
			dialog.text = LinkRandPhrase("Por favor, guarde sua arma, senhor. Isso me deixa nervoso.","Sabe, andar por aí com uma lâmina na mão não é permitido aqui. Guarde isso.","Tenho certeza de que os piratas não vão gostar de ver você andando por aí com uma espada na mão. Eu também não, pra falar a verdade...");
			link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você disser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Por favor, guarde sua arma, senhor. Isso me deixa nervoso.","Sabe, andar por aí com a lâmina na mão não é permitido aqui. Guarde isso.");
				link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Por favor, guarde sua arma, senhor. Isso me deixa nervoso.","Tenho certeza de que os piratas não vão gostar de ver você andando por aí com uma espada na mão. Eu também não, pra falar a verdade...");
				link.l1 = RandPhraseSimple("Entendi.","Eu vou levar isso embora.");
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
