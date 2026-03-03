// диалог начальника шахты
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		location = &Locations[FindLocation(pchar.location)];
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Você tem coragem de aparecer aqui?! Não sei se você é valente ou só um idiota...","Como esses preguiçosos deixaram um inimigo invadir minha residência? Isso me escapa completamente...","Com certeza, meus guardas não valem nem um cobre se esses desgraçados andam soltos por aqui..."),LinkRandPhrase("O que você precisa?"+GetSexPhrase("canalha","fedorento")+"?! Meus soldados já estão no seu encalço, "+GetSexPhrase(", pirata imundo","")+"!","Assassino imundo, saia da minha residência imediatamente! Guardas!","Eu não tenho medo de você, "+GetSexPhrase("rato","vagabunda")+"! Logo você será enforcado em nosso forte, e não irá muito longe depois disso..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Esses soldados não valem um único peso..."," Eles nunca vão me pegar. "),RandPhraseSimple("Cale a boca, "+GetWorkTypeOfMan(npchar,"")+", ou eu arranco essa sua língua imunda!","Eu sugiro que você fique quieto, e talvez consiga sair dessa com vida..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Inimigo na mina! Alarme!";
				link.l1 = "Aaah, diabo!";
				link.l1.go = "fight"; 
				break;
			}	
			dialog.text = LinkRandPhrase(""+TimeGreeting()+", señor. Eu sou "+GetFullName(npchar)+", o engenheiro de minas da mina de Los-Teques. O que te traz aqui?","Olá, senhor. O que você queria?","Hmm... queria alguma coisa de mim, señor? Estou ouvindo.");
			if (!CheckAttribute(location, "quest.info"))
			{
				link.l9 = "Sou novo aqui e gostaria de saber mais sobre esta mina...";
				link.l9.go = "info";
			}
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
			{
				link.l2 = "Tenho uma carga no meu porão que pode te interessar. Escravos para sua mina, para ser exato. Quer negociar?";
				if (!CheckAttribute(location, "quest.slaves")) link.l2.go = "slaves_0";
				else link.l2.go = "slaves";
			}
			link.l1 = "Eu só vim dar um oi, e já estou de saída.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Los-Teques mine extracts gold for the Spanish Crown. Everything we extract belongs to Spain. Here, we find not only gold, but also silver nuggets and valuable precious stones. We don't sell gold here; everything we extract is delivered to the Old World under a reinforced convoy. But we have two exceptions for gold and silver nuggets. First, you can buy a certain amount of them in our local store from the quartermaster. Sometimes salaries don't arrive on time, so we have to keep some coin savings here for such cases; that is why local trading is allowed. Second, we are constantly in need of manpower, so we exchange nuggets for slaves. Therefore, talk to me if you have something to offer, and we will do business. I believe the rules of conduct in the mine are obvious: don't steal, don't distract the convicts, and don't bother the soldiers, otherwise you won't like the consequences.";
			link.l1 = "Bem, obrigado!";			
			link.l1.go = "exit";
			location.quest.info = "true";
		break;
		
		// генератор купли-продажи рабов
		case "slaves_0":
			location.quest.slaves.qty = 200; // стартовая потребность
			dialog.text = "Claro, señor! Quantos você tem?";
			link.l1 = "Eu tenho "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves":
			location.quest.slaves.qty = sti(location.quest.slaves.qty)+GetNpcQuestPastDayParam(location, "slave_date"); // каждый день даёт +1 потребности
			if (sti(location.quest.slaves.qty) > 350) location.quest.slaves.qty = 350; // максимум потребности
			if (sti(location.quest.slaves.qty) < 5)
			{
				dialog.text = "Senhor, infelizmente, no momento não precisamos de mais escravos. Mas a situação pode mudar a qualquer momento, então volte daqui a algumas semanas ou em outra ocasião.";
				link.l1 = "Certo, senhor, entendi. Você não precisa deles agora, mas pode precisar algum dia.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Claro, señor! Quantos você tem?";
				link.l1 = "Eu tenho "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
				link.l1.go = "slaves_1";
			}
		break;
		
		case "slaves_1":
			dialog.text = "Por cada escravo, estou disposto a te pagar ou um lingote de ouro ou dois de prata. Qual você escolhe?";
			link.l1 = "Barras de ouro.";
			link.l1.go = "slaves_g";
			link.l2 = "Barras de prata.";
			link.l2.go = "slaves_s";
			link.l3 = "Me desculpe, señor, mas acabei de mudar de ideia. Fica para outra hora.";
			link.l3.go = "slaves_exit";
		break;
		
		case "slaves_g":
			location.quest.slaves.type = "gold";
			dialog.text = "Certo. Quantos escravos você vai me vender?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_s":
			location.quest.slaves.type = "silver";
			dialog.text = "Certo. Quantos escravos você vai me vender?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_trade":
			iTotalTemp = sti(dialogEditStrings[6]);
			if (iTotalTemp < 1)
			{
				dialog.text = "Senhor, não tenho tempo para piadas idiotas. Se está com vontade de brincar, vá até a taverna!";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
			{
				dialog.text = "Senhor, acho que o senhor precisa descansar. Talvez esteja muito cansado ou tenha sofrido uma insolação. Vá até a taverna, descanse um pouco e depois podemos continuar nossa negociação.";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > sti(location.quest.slaves.qty))
			{
				dialog.text = "Infelizmente, senhor, no momento não precisamos de tantos escravos. A mina atualmente exige "+FindRussianQtyString(sti(location.quest.slaves.qty))+". Vai vender tudo isso?";
				link.l1 = "Sim, claro!";
				link.l1.go = "slaves_max";
				link.l2 = "Hmm... Acho que não sou mesmo.";
				link.l2.go = "slaves_exit";
				break;
			}
			dialog.text = ""+FindRussianQtyString(iTotalTemp)+"? Excelente. Por favor, dê a ordem para levá-los até os portões da cidade. Vou mandar meus homens buscá-los.";
			link.l1 = "Não se preocupe, señor. Seus escravos serão entregues a tempo. Vou emitir todas as ordens necessárias imediatamente.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_max":
			iTotalTemp = sti(location.quest.slaves.qty);
			dialog.text = "Excelente. Por favor, mande que levem eles até os portões da cidade. Vou enviar meus homens para buscá-los.";
			link.l1 = "Não se preocupe, señor. Seus escravos serão entregues a tempo. Vou emitir todas as ordens necessárias imediatamente.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_calk":
			DialogExit();
			Log_Info("Exchange of slaves for ingots has been completed");
			PlaySound("interface\important_item.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,5,10);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
			if (location.quest.slaves.type == "gold") TakeNItems(pchar, "jewelry5", iTotalTemp);
			else TakeNItems(pchar, "jewelry6", iTotalTemp*2);
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
			location.quest.slaves.qty = sti(location.quest.slaves.qty)-iTotalTemp;
		break;
		
		case "slaves_exit":
			DialogExit();
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		    LAi_group_Attack(NPChar, Pchar);
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
