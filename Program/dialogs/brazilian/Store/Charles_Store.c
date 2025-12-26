// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Pode falar, o que você quer?","Estávamos justamente falando sobre isso. Você deve ter se esquecido...","Esta é a terceira vez hoje que você vem com alguma pergunta...","Olha, aqui é uma loja. As pessoas vêm para comprar. Não me atrapalhe!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez da próxima vez.","Certo, por algum motivo eu esqueci...","Sim, realmente é a terceira vez...","Hm, eu não vou...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.Goods"))
			{
				link.l1 = "Você tem minhas mercadorias guardadas no seu armazém. Chá, cacau e pau-santo. Quero retirá-las.";
                link.l1.go = "patria_goods";
			}
			if (CheckAttribute(pchar, "questTemp.Patria.GoodsSM"))
			{
				link.l2 = "Você tem minhas mercadorias de Sint Maarten guardadas no seu armazém. O Barão Noel Forgue as deixou para mim.";
                link.l2.go = "patria_goods_3";
			}
		break;
		
		case "patria_goods":
			dialog.text = "Certo, capitão, tenho suas mercadorias. Tem certeza de que quer levá-las?";
			link.l1 = "Sim.";
			link.l1.go = "patria_goods_1";
			link.l2 = "Espere um pouco, preciso verificar se há espaço suficiente no porão primeiro.";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_1":
			dialog.text = "Perfeito. Vou pedir aos carregadores para entregar no cais.";
			link.l1 = "Fechado!";
			link.l1.go = "patria_goods_2";
		break;
		
		case "patria_goods_2":
			DialogExit();
			WaitDate("", 0, 0, 0, 4, 10); //крутим время
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.Patria.Goods");
			SetCharacterGoods(pchar, GOOD_COFFEE, GetCargoGoods(pchar, GOOD_COFFEE) + 500);
			SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE) + 500);
			SetCharacterGoods(pchar, GOOD_SANDAL, GetCargoGoods(pchar, GOOD_SANDAL) + 50);
		break;
		
		case "patria_goods_3":
			dialog.text = "Sim, exatamente. Eu os mantenho aqui por ordem do barão. Tem certeza de que quer levá-los?";
			link.l1 = "Sim.";
			link.l1.go = "patria_goods_4";
			link.l2 = "Espere um pouco, preciso verificar se há espaço suficiente no porão primeiro.";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_4":
			dialog.text = "Perfeito. Vou pedir aos carregadores para entregar no cais.";
			link.l1 = "Fechado!";
			link.l1.go = "patria_goods_5";
		break;
		
		case "patria_goods_5":
			DialogExit();
			WaitDate("", 0, 0, 0, 4, 10); //крутим время
			RecalculateJumpTable();
			StoreDayUpdate();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.Patria.GoodsSM"); // 17-add
			SetCharacterGoods(pchar, GOOD_TOBACCO, GetCargoGoods(pchar, GOOD_TOBACCO) + 500);
			SetCharacterGoods(pchar, GOOD_EBONY, GetCargoGoods(pchar, GOOD_EBONY) + 200);
			SetCharacterGoods(pchar, GOOD_MAHOGANY, GetCargoGoods(pchar, GOOD_MAHOGANY) + 250);
			SetCharacterGoods(pchar, GOOD_GOLD, GetCargoGoods(pchar, GOOD_GOLD) + 200);
			SetCharacterGoods(pchar, GOOD_SILVER, GetCargoGoods(pchar, GOOD_SILVER) + 400);
			SetCharacterGoods(pchar, GOOD_SHIPSILK, GetCargoGoods(pchar, GOOD_SHIPSILK) + 200);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
