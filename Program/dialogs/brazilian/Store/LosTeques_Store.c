void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Levantaram um alarme na cidade. Estão todos te procurando! Eu não ficaria aqui por muito tempo se fosse você.","A guarda da cidade inteira está vasculhando a cidade tentando te encontrar. Eu não sou idiota e não vou falar com você!","Corre, amigo, antes que os soldados te transformem em carne moída..."),LinkRandPhrase("O que você quer, canalha?! A guarda da cidade está no seu encalço neste momento. Você não vai longe, pirata imundo!","Saia da minha casa, assassino! Guardas!!","Eu não tenho medo de você, moleque! Logo vão te enforcar, você não vai escapar..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, não estou muito preocupado com o alarme...","Eles não têm a menor chance de me pegar."),RandPhraseSimple("Cale a boca, "+GetWorkTypeOfMan(npchar,"")+", ou eu arranco essa sua língua maldita!","Heh, "+GetWorkTypeOfMan(npchar,"")+", você também quer caçar um pirata! Olha, amigo, mantenha a calma e você vai sobreviver..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"! Nunca te vi antes, señor. Posso presumir que é um capitão... Acertei? Meu nome é "+GetFullName(npchar)+", e minha loja está ao seu dispor. Ouro, prata e muito mais para despertar o interesse de um homem curioso.";
				Link.l1 = "Entendi. Eu sou "+GetFullName(pchar)+". Prazer em conhecê-lo, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", señor! Fico feliz em vê-lo novamente na minha loja. Gostaria de adquirir algumas pepitas de ouro? Ou talvez hoje se interesse por minerais?";
				link.l1 = "Mostre-me sua mercadoria, "+npchar.name+".";
				link.l1.go = "trade";
				link.l4 = "Não, não preciso de nada, "+npchar.name+". Só passei aqui para te cumprimentar.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Assim como eu, senhor. Gostaria de dar uma olhada nas minhas mercadorias? Tenho certeza de que há algo aqui que vai lhe interessar.";
			link.l1 = "É a minha primeira vez aqui e gostaria de saber um pouco mais sobre este povoado.";
			link.l1.go = "info";
			link.l2 = "Então me mostre o que você tem à venda.";
			link.l2.go = "trade";
		break;
		
		case "info":
			dialog.text = "Our small town was built thanks to the gold mine. They extract gold ore, silver, and golden nuggets. Sometimes even gems. We used to have only a garrison here until friendly Indians and some white settlers joined us\nIgnacio Ortega built a tavern and made our lives a bit cheerier. All kinds of adventurers visit this place with the foolish intention of robbing us. We don't have a court here, so their numbers dropped after we hanged several idiots right in the middle of town\nGold ore is sent to the ships under the protection of soldiers and friendly Indians; nuggets, however, you can buy right here in this store\nBesides, I sometimes have very interesting minerals to offer, so visit me when you have time, I always resupply my stock.";
			link.l1 = "Obrigado pela história interessante! Vou me lembrar disso.";			
			link.l1.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Assalto em plena luz do dia!!! O que está acontecendo aqui?! Espere, calma, amigo...","Ei, o que você está fazendo aí?! Tentando me roubar? Agora você se ferrou...","Espera aí, que diabos você está fazendo? Então você é um ladrão! Considere isso o fim da linha, seu desgraçado...");
			link.l1 = LinkRandPhrase("Diabo!!","Caramba!!","Ah, merda!");
			link.l1.go = "fight_owner";
		break;
		
		case "fight_owner": // лесник . выход из диалога . если копался в сундуках. 
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}
