void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- леди в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (LAi_grp_playeralarm <= 0 && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Done") && !CheckAttribute(npchar, "quest.chickengod") && sti(npchar.nation) == SPAIN) {
				link.chickengod = "Senora, please excuse me, but I was asked to tell you that you have... a date inside an old pagan pyramid.";
				link.chickengod.go = "chickengod";
			}
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Jesus! Um homem tão desprezível nos meus aposentos! Saia daqui ou vou chamar os guardas!","Isso não pode estar acontecendo... Quem deixou esse rato entrar na minha casa? Cai fora daqui, seu desgraçado! Você não tem nada que fazer aqui! Vai embora!","Que tempos estranhos estamos vivendo. Ratos estão invadindo meu quarto! Vai embora!");
				link.l1 = RandPhraseSimple("Calma aí...","Cuidado com o que diz...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("O que você está fazendo no meu quarto? Saia daqui!","Que vergonha! Peço que você saia deste lugar imediatamente!","Com licença, senhor, mas você não foi convidado aqui. Por favor, saia do meu quarto!");
				link.l1 = RandPhraseSimple("Com licença... Estou de saída.","Desculpe, porta errada. Preciso ir.");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "Ah, o que foi isso?! Que tola eu sou! Andando por aí, nem vi nada... Guardas!!!";
			link.l1 = "Cale a boca!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Saia daqui, rato!","Saia imediatamente da propriedade do governador, rato!","Não me importa o que você está fazendo na casa do governador de "+XI_ConvertString("Colony"+npchar.city+"Gen")+"Mas o meu conselho é: cai fora agora!");
				link.l1 = RandPhraseSimple("Calma aí, camarada...","Cuidado com o que diz!");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Saudações! Sou o criado do governador. Meu nome é "+GetFullName(NPChar)+".","Eu cuido deste lugar, "+GetAddress_Form(NPChar)+".","Sabe, "+GetAddress_Form(NPChar)+", nosso governador é um bom homem e nos paga bem...");
				link.l1 = RandPhraseSimple("Legal.","Hum, tudo bem...");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "Então você decidiu roubar o governador?! Guardas, peguem o ladrão!!";
			link.l1 = "Cale a boca!";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("É melhor você sair daqui, "+GetSexPhrase("amigo","garota")+"...","Vá embora!","Errou a porta, "+GetSexPhrase("amigo","garota")+"? ? Esta propriedade pertence ao governador de "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				link.l1 = RandPhraseSimple("Eu vou embora quando eu quiser!","Isso não é da sua conta...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Hoje, fui designado para servir aqui. Lugar agradável...","Eu protejo a propriedade de "+GetAddress_Form(NPChar)+".","Minhas ordens são proteger a propriedade do governador.");
				link.l1 = RandPhraseSimple("Boa sorte, então...","Hum, entendi...");
				link.l1.go = "exit";
			}
		break;
		
		case "chickengod":
			pchar.questTemp.ChickenGod.Tasks.o2.Counter = sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) + 1;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) >= 3) {
				dialog.text = "Ah, sim. Finalmente! Estou pronto para ir com você, capitão.";
				link.l1 = "Assim mesmo? Señora, tem certeza de que é isso que deseja?";
				link.l1.go = "chickengod_accept";
			} else {
				sld = CharacterFromID(npchar.city + "_Mayor");
				dialog.text = "O quê?! Você está bêbado, señor? Que piada idiota! Por favor, vá embora, eu lhe imploro! "+sld.name+"! Guardas! Socorro!";
				link.l1 = "Merda, hora de ir.";
				link.l1.go = "chickengod_decline";
			}
			npchar.quest.chickengod = true;
		break;
		
		case "chickengod_accept":
			dialog.text = "Mas é claro! Ah, o Senhor Aruba e eu mantemos uma correspondência há muito tempo!";
			link.l1 = "Se é assim, por favor, suba a bordo!";
			link.l1.go = "chickengod_accept_take";
			link.l2 = "Não, senhora, isso não vai dar certo. Minha honra não permite que uma mulher seja colocada em perigo, e está claro que a senhora foi enganada!";
			link.l2.go = "chickengod_accept_nottake";
		break;
		
		case "chickengod_accept_take":
			DialogExit();
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			pchar.questTemp.ChickenGod.Tasks.o2.Lady = npchar.id;
			AddDialogExitQuestFunction("ChickenGod_TakeLady");
		break;
		
		case "chickengod_accept_nottake":
			dialog.text = "Nesse caso, meu caro capitão, pegue esse seu senso de honra rústico e enfie no seu rabo! Vou esperar outro mensageiro, alguém menos cabeça-fechada que você!";
			link.l1 = "Encantador!";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			SetFunctionTimerCondition("ChickenGod_NotTakeLadyConsequence", 0, 1, 0, false);
		break;
		
		case "chickengod_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_LadyRefuse");
		break;
		
	}
}
