// Виктор Кассель - бандит
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
				dialog.text = "Cai fora, camarada. Não quero papo com quem provoca gente inocente pra brigar. Dá o fora!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hm... O que você quer, camarada? Se veio conversar, vou ter que te decepcionar...";
				link.l1 = "Que pena... Eu queria mesmo conversar. Sou novo aqui e estou só começando a conhecer as pessoas...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! O que você quer?";
				link.l1 = LinkRandPhrase("Victor! Tem alguma novidade pra mim?","Aconteceu alguma novidade na ilha?","Vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está. Tchau.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Um novato? Hm... Muito bem. Sou Victor Cassel, e é melhor você não me irritar quando estou de mau humor. E nem quando estou de bom humor. Não perco tempo com conversa fiada – se alguém força a barra, eu revido. E revido forte. ";
			link.l1 = "Eu sou "+GetFullName(pchar)+", e eu também posso insistir, mas espero que não seja necessário. Se você não quiser conversar, não vou te incomodar. Tchau.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Victor! Tem alguma novidade pra mim?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quero te fazer algumas perguntas sobre a ilha.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Seja rápido.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Como você veio parar aqui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Como é a vida aqui?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Quem é a pessoa mais importante aqui?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Onde posso ganhar dinheiro na ilha?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Com licença...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Por que você se importa? Não quero falar sobre isso, principalmente com um homem que eu nem conheço.";
			link.l1 = "Jesus... desculpa.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Parece um tédio. Um tédio cansativo, monótono, sem sentido. Vou me juntar aos piratas do Tubarão – pelo menos aqueles caras arranjam uma briga de vez em quando. Tenho certeza de que um dia eles vão encontrar um jeito de sair da ilha também. Quando esse dia chegar, quero estar com eles.";
			link.l1 = "Sério...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "O Almirante, com certeza! Ele tem os Narvais e os Rivados na palma da mão e eles não podem fazer nada a respeito. Depois dele, vêm os líderes dos clãs: Donald Greenspy dos Narvais e Black Eddy dos Rivados. Em seguida, Axel Yost, um mercador Narval. Depois, o dono da taverna, Sancho Carpentero – ninguém aguenta aqui sem uma bebida forte, heh!";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Chests, of course, but you have to beat the locks, first; people don't trust each other here, so all chests have locks. And let me tell you, pal, the best trinkets are kept inside the ships under the watch of their owners.\nYou can also explore the outer ring, but take care not to fall through the rotten decks. Or you can hunt giant crabs; you can get a good price for the meat on their pincers.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ei, seu desgraçado! Eu falei pra não bancar o espertinho comigo. Tira as mãos do meu peito!","Eu sabia que você era do tipo insistente. Vou te mostrar o que acontece quando tentam me roubar!","Ah, que bom, eu estava procurando uma desculpa pra ser insistente com você!");
			link.l1 = "Argh!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "O quê?! Resolveu saquear meus baús? Você não vai sair impune dessa!";
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
			dialog.text = LinkRandPhrase("Amigo, guarda essa espada. Você está ridículo.","Sabe, camarada, o Tubarão vai te jogar no Tártaro se você não guardar isso...","Vai se catar com essa espada, você tá parecendo um idiota.");
			link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você disser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Amigo, guarda essa espada. Você está ridículo.","Sabe, camarada, o Tubarão vai te jogar no Tártaro se você não guardar isso...");
				link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Amigo, guarda essa espada. Você está ridículo.","Vai se foder com essa espada, você está parecendo um idiota.");
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
