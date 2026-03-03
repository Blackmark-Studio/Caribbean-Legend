//Jason общий диалог уличных матросов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew"))//найм в команду
				{
					dialog.text = "Bom dia, "+GetAddress_Form(NPChar)+". Eu sei que você é o capitão do seu próprio navio. Tenho uma proposta para você.";
					link.l1 = "Estou ouvindo, "+GetAddress_FormToNPC(NPChar)+". Que tipo de acordo?";
					link.l1.go = "crew";
					link.l2 = "Desculpe, "+GetAddress_FormToNPC(NPChar)+", mas estou com pressa.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Ei, capitão! O que você quer de um simples marinheiro?","Bom dia, senhor. Em que posso ajudar?","Bom dia, senhor. Precisa de alguma coisa?");
				link.l1 = "Prazer em te conhecer, camarada! Meu nome é "+GetFullName(pchar)+". Tem um minuto pra conversar?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Tenho uma pergunta pra você.","Preciso de algumas informações sobre esta colônia.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Só queria dizer oi. Até mais!";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Você de novo, senhor? O que mais deseja?";
				link.l1 = "Tem um minuto pra conversar?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Tenho uma pergunta pra você.","Preciso de algumas informações sobre esta colônia.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Não, amigo, não é nada. Boa sorte!";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" às suas ordens, senhor! O que deseja saber?","Que bom falar com você, Capitão!","Bem... Acho que ainda tenho um tempinho pra conversar...","Infelizmente, preciso ir agora. Adeus!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tem alguma novidade interessante pra me contar?","Tem alguma novidade interessante pra me contar?","Tem alguma coisa interessante pra me contar?","Claro. Boa sorte!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
		break;

		case "crew":
			switch (hrand(2))
			{
				case 0: sTemp = "Me and my messmates were put shoreside from our last ship due to various sickness and injuries. But we are all healthy now and want to get back to work as sailors again. Do you want to hire us?"; break;
				case 1: sTemp = "Me and a few of my boys were paid off from a merchantman due to the end of its contract. We have been without a single piece of eight for a long time already so we want to get back to work again. Do you need some skillful sailors for your crew?"; break;
				case 2: sTemp = "Me and my mates just got back from a voyage two weeks ago. The ship's master has dismissed us and we've been having some great fun. But our pockets are empty now so it's time to set sail again. Do you want to hire us, captain?"; break;
			}
			dialog.text = sTemp;
			link.l1 = "Bem, estou pronto para ouvir sua proposta. Quantos são vocês, e quais são suas habilidades?";
			link.l1.go = "crew_1";
			link.l2 = "Sinto muito, marinheiro, mas já tenho homens suficientes. Procure outro capitão para servir.";
			link.l2.go = "exit";
		break;
		
		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = "We are the best in working with sails and tackles. Not being overly modest, I'd say that we are professionals at ship handling, so don't worry, we won't let you down even in the strongest storms."; break;
				case 1: sTemp = "Most of all we like to be on the gun deck. Few of us even served on real warships. We can load and fire cannons in the way no one in your crew can. You can count on us in every hard fight!"; break;
				case 2: sTemp = "We're proper good boarders captain, did a few runs on privateers before this. We know the glitter of cutlasses and the smell of gunpowder and blood. That's our calling. It's not easy to defeat us in a hand-to-hand fight so you can always count on our blades, captain!"; break;
			}
			dialog.text = "Há "+sti(npchar.quest.crew.qty)+" de nós e só aceitaremos ser contratados juntos. Podemos realizar todas as tarefas básicas de marinheiro."+sTemp+"";
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = "Parece que são os homens que estou procurando. E quanto ao seu adiantamento?";
				link.l1.go = "crew_2";
				link.l2 = "Desculpe, marinheiro, mas preciso de outras habilidades no momento. Você deveria procurar outro capitão.";
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = "Desculpe, marinheiro, mas não tenho espaço suficiente no meu navio. Você deveria procurar outro capitão.";
				link.l1.go = "exit";
			}
		break;
		
		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" para cada um. E depois, o salário mensal de um marinheiro comum. Não vamos pedir nada exagerado, capitão.";
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = "Você está contratado! Pegue suas moedas. Agora vá para o meu navio, ele se chama '"+pchar.ship.name+"', bem ali no porto. O contramestre vai designar redes para todos vocês nos alojamentos da tripulação e organizar as refeições.";
				link.l1.go = "crew_3";
			}
			link.l2 = "Infelizmente, não posso pagar por todos vocês. Vocês deveriam procurar outro capitão.";
			link.l2.go = "exit";
		break;
		
		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "Sim, capitão! Vou reunir os rapazes e partiremos imediatamente.";
			link.l1 = "Seja rápido, zarpamos a qualquer momento.";
			link.l1.go = "crew_4";
		break;
		
		case "crew_4":
			DialogExit();
			AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
			//увеличиваем опыт
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(pchar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(pchar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(pchar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(pchar, "Soldiers", iTemp); break;
			}
			//увеличиваем мораль
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(pchar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ei, guarde sua espada, capitão. Ninguém aqui quer confusão, certo?","Ei, guarde sua espada, capitão. Ninguém aqui quer confusão, certo?");
			link.l1 = LinkRandPhrase("Certo.","Como quiser.","Como você disser.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
