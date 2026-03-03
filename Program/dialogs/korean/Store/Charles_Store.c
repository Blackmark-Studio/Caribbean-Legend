// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("어서 말해, 뭘 원하는가?","바로 그 얘기를 하고 있었소. 당신이 잊은 게 분명하군...","오늘만 세 번째로 뭔가를 또 물어보는군...","이봐, 여긴 가게야. 사람들은 여기서 물건을 사 간다고. 나 좀 방해하지 마!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 아마 다음 기회에.","맞아요, 무슨 이유에선지 잊고 있었네요...","그래, 정말로 이번이 세 번째야...","흠, 나는 안 하겠어...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.Goods"))
			{
				link.l1 = "당신 창고에 내 물건이 보관되어 있소. 차, 코코아, 그리고 리그넘바이타. 그것들을 찾아가고 싶소.";
                link.l1.go = "patria_goods";
			}
			if (CheckAttribute(pchar, "questTemp.Patria.GoodsSM"))
			{
				link.l2 = "당신 창고에 신트마르턴에서 온 내 물건이 보관되어 있소. 바론 노엘 포르그가 그것들을 내게 남겼소.";
                link.l2.go = "patria_goods_3";
			}
		break;
		
		case "patria_goods":
			dialog.text = "맞습니다, 선장님, 물건은 준비되어 있습니다. 정말로 가져가시겠습니까?";
			link.l1 = "예.";
			link.l1.go = "patria_goods_1";
			link.l2 = "잠깐만, 먼저 창고에 공간이 충분한지 확인해야 해.";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_1":
			dialog.text = "완벽하군. 짐꾼들에게 부두로 옮기라고 명령하겠네.";
			link.l1 = "거래 성사요!";
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
			dialog.text = "예, 맞습니다. 남작의 명령으로 여기 보관하고 있지요. 정말로 가져가시겠습니까?";
			link.l1 = "예.";
			link.l1.go = "patria_goods_4";
			link.l2 = "잠깐만, 먼저 선창에 공간이 충분한지 확인해야 해.";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_4":
			dialog.text = "완벽하군. 짐꾼들에게 부두로 가져다 주라고 명령하겠다.";
			link.l1 = "거래 성사!";
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
