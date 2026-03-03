// Жаклин Тьюрам - торговый капитан
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
				dialog.text = "Não quero falar com você. Você ataca civis inocentes sem motivo e provoca brigas. Au revoir!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bom dia, monsieur. Você é novo aqui, não é?";
				link.l1 = TimeGreeting()+". Sim, acho que sou mesmo. Meu nome é "+GetFullName(pchar)+". E você é?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, bonjour "+GetFullName(pchar)+"! "+TimeGreeting()+"! Como posso te ajudar hoje?";
				link.l1 = LinkRandPhrase("Bonjour, Monsieur Turam! Conte-me as novidades.","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está. Au revoir!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Jacques Turam. Two years ago I was a respectable and wealthy merchant, owner and captain of my own fluyt. Alas, now I am as poor as a church mouse with no hope that my situation will change.\nSome people get lucky here; they find gold, jewels, ships filled with treasure, but I am not one of them. I found only a single chest of doubloons and few trinkets.\nAt least it's enough to buy food, so I don't starve... Pleasure to meet you, sir, I don't mind chatting.";
			link.l1 = "Também fico feliz em te conhecer, Jacques. Au revoir!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Bonjour, Monsieur Turam! Conte-me as novidades.","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
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
				link.l2 = "O que você faz aqui?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Me diga... Vejo que há mulheres na ilha...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Você quer voltar, para o mundo lá fora?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Não é nada.";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "You want to hear my story? Fine. As you already know, I was a merchant. One day I sailed from Tortuga to Belize on my good old fluyt. My holds were filled with ebony and cacao - I spent all my money on the cargo.\nI'd arranged a very profitable deal with a man who wanted to buy my cargo for an extremely high price. I would've made a fortune. All was going well, not a single cloud in the sky, my ship as swift as a bird. Then trouble came.\nI was sailing near Cuba, avoiding Spanish patrols, when suddenly we were attacked by a pirate galleon. What were they doing there, in the middle of Spanish territory? We tried to flee, but the galleon was surprisingly fast.\nThe pirates caught us up and attacked. Their couleuvrines were loaded with grape shot - the first salvo took out half my crew demoralized the rest. I wanted to put up a good fight, but my crew and officers stopped me. We surrendered.\nThe pirates took our cargo and threw away our cannons. I hoped it was not the end for me; losing the cargo was a heavy blow, but I could still make money on freight contracts and until I got back on my feet.\nBut fate had other plans. The pirate bastards opened fire on my defenseless fluyt - we were a sitting duck without our guns. I can still hear the pirates' laughter...\nThe galleon sailed away and we clung to the wreck of our ship. Then a strong gale came and a wave carried me overboard. I managed to lash myself to a broken spar and stay afloat.\nI'll spare you the details about my brush with sharks. After an eternity the currents brought me to this island. That's how I survived.";
			link.l1 = "Sim, essa é realmente uma história triste.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Eu vivo como o resto dos moradores: procuro objetos de valor no anel externo e troco por comida. Sonho em encontrar os tesouros de um chefe indígena, ou um galeão carregado de ouro espanhol...\nSonho em comer algo diferente de carne salgada e peixe – houve um homem aqui que caçava aqueles caranguejos gigantes. Eu costumava pagar cinco dobrões por garra e me alimentar disso por vários dias.\nUma pena que ele morreu... embora ninguém tenha ficado surpreso – caçar esses caranguejos é perigoso demais.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "I see what you're implying. Yes, love and intrigue exist here - and why wouldn't they? Man is made for woman as woman is made for man. That's nature. You may try Gillian and Tanneke; they are young, pretty and open to courting.\nI myself have already found a woman: Natalia. She is a waitress in Sancho's tavern. A great girl, I tell you. I believe she is the only reason I didn't lose my mind during those first months living here. She has helped me a lot and now we are together.";
			link.l1 = "Ah, romântico!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Boa pergunta. Eu gostaria disso, claro. Mas pensando bem... Estou quebrado. Investi tudo na minha carga e agora tanto ela quanto meu navio afundaram. Não me sobrou nada. A única maneira que vejo de ganhar dinheiro agora é trabalhar para a Companhia Holandesa das Índias Ocidentais – se eles me aceitarem, claro. Se ao menos eu tivesse dinheiro suficiente para comprar uma escuna e alguns mantimentos... mas não tenho, então é melhor eu ficar na ilha. Pelo menos aqui não preciso trabalhar de sol a sol por um pedaço de pão.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Quem é - ah, ladrão!","Tire as mãos das minhas coisas, seu demônio!","Esse baú é meu! Fique longe dele!");
			link.l1 = "Droga!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Como você ousa mexer nas minhas gavetas!";
			link.l1 = "Silêncio!";
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
			dialog.text = LinkRandPhrase("Monsieur, por favor, guarde sua arma. Você está me assustando.","Sabe, você pode acabar se machucando, correndo por aí com a arma desembainhada.","Não tente impressionar as moças, bancando o cavalheiro. Guarde isso...");
			link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Ah, certo...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Monsieur, como cidadão desta ilha, peço que guarde sua lâmina.","É perigoso andar por aí com uma arma na mão, monsieur. Por favor, guarde-a.");
				link.l1 = LinkRandPhrase("Tudo bem.","Muito bem, então.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Monsieur, por favor, guarde sua arma. Você está me assustando.","Não gosto quando homens agem como piratas, andando por aí com a arma em punho.");
				link.l1 = RandPhraseSimple("Me desculpe, estou guardando isso.","Estou guardando isso.");
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
