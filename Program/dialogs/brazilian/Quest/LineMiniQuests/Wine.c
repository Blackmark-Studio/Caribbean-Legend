void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Isto é um bug. Avise os desenvolvedores.";
			link.l1 = "Claro!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Wine_fort":
			dialog.text = "Trouxe a garrafa?";
			if (CheckCharacterItem(pchar, "potionwine"))
			{
				link.l1 = "Sim, fui eu mesmo. Paguei 700 pesos por isso, então espero receber 1.000 pesos de você.";
				link.l1.go = "Wine_fort_1";
			}
			link.l2 = "Não, estou cuidando disso.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort";
		break;
	
		case "Wine_fort_1":
			AddMoneyToCharacter(pchar, 1000);
			RemoveItems(PChar, "potionwine", 1);
			dialog.text = "Deus seja louvado, eu já estava morrendo de sede. Muito obrigado, senhor! Aqui está o seu milhar, e eu fico com a sua garrafa, haha! Olha só, já que estamos fazendo bons negócios aqui, tenho mais um pedido pra você\nSerá que você consegue trazer mais vinho pra mim e meus amigos, pra... usos futuros? Acabamos de dar um jeito numa quadrilha de contrabandistas, então moedas não faltam, hehe...";
			link.l1 = "Desculpa, camarada, não tenho tempo pra buscar mais bebida pra você.";
			link.l1.go = "Wine_fort_exit";
			link.l2 = "Dinheiro é sempre bem-vindo. Quantas garrafas você precisa?";
			link.l2.go = "Wine_fort_2";
		break;
	
	case "Wine_fort_exit":
			DelLandQuestMark(npchar);
			WineTraderQMDel();
			dialog.text = "Como quiser. De qualquer forma, obrigado pela ajuda! Saúde, e tudo de bom pra você!";
			link.l1 = "Continue assim, soldado!";
			link.l1.go = "exit";
			sld = characterFromId(pchar.questTemp.Wine.id);	
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			pchar.questTemp.Wine.fail = "true";
			CloseQuestHeader("Wine");
	break;
	
		case "Wine_fort_2":
			dialog.text = "A mil peças de oito por garrafa, podemos comprar sessenta garrafas, mas não mais do que isso. Mas também não traga menos de dez — isso só vai deixar a gente com mais sede!";
			link.l1 = "Entendido, não mais que 60 garrafas e não menos que dez. Vou trazer seu vinho.";
			link.l1.go = "Wine_fort_3";
		break;
	
		case "Wine_fort_3":
			dialog.text = "Benditos sejam os pés que trazem boas notícias de uma boa bebida! Estou contando com você, capitão. Ah, quase me esqueci! Você precisa trazer a bebida em menos de uma semana, porque minha companhia naval será transferida para a frota em sete dias e vamos ficar fora por alguns meses depois que partirmos.";
			link.l1 = "Entendi. Vou tentar ser rápido.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.bottles = "true";
			npchar.lifeday = 7;
			AddQuestRecord("Wine", "1");
			AddQuestUserData("Wine", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Wine.City+"Gen"));
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.SName);
			SetFunctionTimerCondition("Soldier_wait", 0, 0, 7, false);
			NextDiag.TempNode = "Wine_fort_check";
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
	
		case "Wine_fort_check":
			dialog.text = "Então, capitão, trouxe o vinho?";
			if (sti(pchar.items.potionwine) >= 10)
			{
				link.l1 = "Sim, eu tenho.";
				link.l1.go = "Wine_take";
			}
			link.l2 = "Não. Ainda estou trabalhando nisso.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_take":
			pchar.questTemp.Wine.Qty = sti(pchar.items.potionwine);
			pchar.questTemp.Wine.Money = sti(pchar.questTemp.Wine.Qty)*1000;
			if (sti(pchar.items.potionwine) > 60)
			{
				dialog.text = "Holy Saint Arnulf, pray for us! That's a lot of wine! Excellent! Regrettably, as I said, we can only afford sixty bottles; unfortunately, we don't have enough money to buy more. Take your pesos and I'll take good care of these sixty bottles. Please keep the rest.";
				link.l1 = "Obrigado. Não deixe de brindar à minha saúde junto com seus amigos soldados!";
				link.l1.go = "Wine_take_1";
				pchar.questTemp.Wine.Money = 60000;
				RemoveItems(PChar, "potionwine", 60);
			}
			else
			{
				dialog.text = "Bem-vindo de volta. Vamos ver... Você trouxe "+sti(pchar.questTemp.Wine.Qty)+" garrafas. Ótimo! Vou ficar com elas. O pagamento é "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Money))".";
				link.l1 = "Obrigado. Não esqueça de brindar à minha saúde junto com seus amigos soldados!";
				link.l1.go = "Wine_take_1";
				RemoveItems(PChar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			}
		break;
	
		case "Wine_take_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.Wine.Money));
			dialog.text = "Com certeza vamos, "+GetAddress_Form(NPChar)+"! O tambor está tocando a chamada, preciso ir agora. Adeus!";
			link.l1 = "Bons ventos e mares tranquilos, camarada!";
			link.l1.go = "Wine_take_2";
		break;
	
		case "Wine_take_2":
			DelLandQuestMark(npchar);
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info ("You handed over the wine");
			pchar.quest.Soldier_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.City");
			sld = characterFromId(pchar.questTemp.Wine.id);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
