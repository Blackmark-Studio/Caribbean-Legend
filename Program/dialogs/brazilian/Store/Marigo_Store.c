// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Pode falar, o que você quer?","Acabamos de falar sobre isso. Você deve ter esquecido...","Essa é a terceira vez hoje que você faz essa pergunta...","Escute, isto é uma loja. As pessoas vêm aqui para comprar. Não me atrapalhe!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez na próxima vez.","Certo, por algum motivo eu esqueci...","Sim, realmente é a terceira vez...","Hm, eu não vou...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason --> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Findcloves" && !CheckAttribute(npchar, "quest.Portugal"))
			{
   				link.l1 = "Escute, preciso de roupas elegantes. Quero algo caro, quero parecer um verdadeiro nobre. Você tem algo assim?";
				link.l1.go = "Portugal_cloves";
			}
			//<-- Португалец
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten")
			{
				link.l1 = "Um galeão chamado 'Admirável' trouxe recentemente uma carga de peles para você. Lembra disso?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		//Jason --> Португалец
		case "Portugal_cloves":
			dialog.text = "Roupas nobres? Claro, tenho um conjunto aqui: calças, gibão, camisa de seda e botas. Custa 20.000 pesos. As roupas são de altíssima qualidade, são confortáveis e têm um visual impressionante, então não aceito menos por elas.";
			if (sti(pchar.money) >= 20000)
			{
				link.l1 = "Ótimo! Entregue.";
				link.l1.go = "Portugal_cloves_1";
			}
			link.l2 = "Hm... Eu não tenho tanto dinheiro assim no momento.";
			link.l2.go = "Portugal_cloves_nomoney";
		break;
		
		case "Portugal_cloves_nomoney":
			dialog.text = "Então volte quando tiver o dinheiro.";
			link.l1 = "Tudo bem. Eu volto já!";
			link.l1.go = "exit";
		break;
		
		case "Portugal_cloves_1":
			AddMoneyToCharacter(pchar, -20000);
			GiveItem2Character(pchar, "suit_1");
			Log_Info("You've received expensive clothing");
			PlaySound("interface\important_item.wav");
			dialog.text = "Aqui está.";
			link.l1 = "Obrigado!";
			link.l1.go = "exit";
			npchar.quest.Portugal = "true";
			sld = characterFromId("PortugalDoctor");
			sld.dialog.currentnode = "Portugal_doctor_4";
			DelLandQuestMark(characterFromId("Marigo_trader"));
			AddLandQuestMark(characterFromId("PortugalDoctor"), "questmarkmain");
			QuestPointerDelLoc("marigo_town", "reload", "reload6_back");
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		//<-- Португалец
		case "guardoftruth":
			dialog.text = "Sim. Ele chegou na hora, descarregou a mercadoria e eu paguei como havíamos combinado. Por que está perguntando?";
			link.l1 = "O capitão daquele navio é Gaius Marchais, um velho conhecido meu. Estou tentando encontrá-lo. Você saberia me dizer o que ele fez depois disso? Talvez tenha fornecido alguma carga extra para ele, ou ele comentou para onde estava indo?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Nothing of that. I didn't offer him any freight; he didn't even ask for it. He didn't share his plans for the future with me. I don't even remember all the details, do you know how many people have come in and out of here since that time? He unloaded and sailed off and that's all I can say about him.";
			link.l1 = "Tudo bem. De qualquer forma, obrigado. Tudo de bom!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "11");
			pchar.questTemp.Guardoftruth = "maarten1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
