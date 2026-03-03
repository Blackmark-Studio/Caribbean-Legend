// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있으십니까?","무엇을 도와드릴까요?"),"얼마 전에 나한테 그 질문을 하려고 했었지...","그래, 맞지... 또 빙빙 돌고 있는 거냐?","이봐, 여기서 재정은 내가 맡아. 질문엔 답하지 않아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없소."),"음, 내 기억이 다 어디로 갔지...","맞췄군, 미안하다...","알겠습니다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит, Голландия
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				link.l1 = "나리, 나는 선장이오 "+GetFullName(pchar)+", 그리고 나는 루카스 로덴부르크의 부탁을 받고 왔소. 그가 당신에게 맡긴 소포를 가지고 있소.";
				link.l1.go = "SantiagoTripBank";	
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripReturn")
			{
				link.l1 = "루카스 로덴부르크 나리의 답변을 받으러 왔소.";
				link.l1.go = "SantiagoTripBank_3";	
			}
			//Голландский гамбит, Голландия
		break;
		
		case "SantiagoTripBank":
			if (GetCharacterItem(pchar, "Chest") >= 5)
			{
			dialog.text = "상상해 보시오... 소포라니! 자, 이리 내시오, 나리.";
			link.l1 = "또한, 로덴부르크 나리가 이것을 전해 달라고 했소...";
			link.l1.go = "SantiagoTripBank_1";
			RemoveItems(PChar, "NPC_Letter", 1);
			RemoveItems(PChar, "Chest", 5);
			DelLandQuestMark(npchar);
			}
			else
			{
			dialog.text = "내가 알기로는, 소포 말고도 내가 받아야 할 다른 것이 있었던 것 같은데, 선장. 그러니... 그건 어디 있지? 내가 무슨 말 하는지 알겠나?";
			link.l1 = "물론이지! 상자들은 내 배에서 철저히 감시되고 있어. 곧바로 너한테 가져다주지.";
			link.l1.go = "exit";
			}
		break;
		
		case "SantiagoTripBank_1":
			dialog.text = "흠... 흥미롭군. 그가 '유감'을 전한다니. 그래, 그래. 하지만 로덴부르크 나리의 유감 표명은 꽤 설득력이 있어서 거절하기가 어렵소. 나리, 적절한 답장을 쓰려면 시간이 좀 걸릴 것이니, 내일 정오쯤 다시 와서 답장을 받아가 주시겠소? 선술집에서 쉬거나, 도시를 둘러보시오. 산티아고에는 볼거리가 많으니.";
			link.l1 = "좋소, 내일 정오쯤 다시 오겠소. 그때 뵙겠소, 나리.";
			link.l1.go = "SantiagoTripBank_2";
		break;
		
		case "SantiagoTripBank_2":
			DialogExit();
			pchar.quest.SantiagoTripOver.over = "yes"; //снять таймер
			bDisableFastReload = true;
			pchar.quest.Santiago_Trip.win_condition.l1 = "location";
			pchar.quest.Santiago_Trip.win_condition.l1.location = "Santiago_town";
			pchar.quest.Santiago_Trip.function = "SantiagoTrip_Attack";
			pchar.questTemp.HWIC.Holl = "SantiagoTripAttack";
			LAi_LocationDisableOfficersGen("Santiago_town", true);//офицеров не пускать // 291112
		break;
		
		case "SantiagoTripBank_3":
			dialog.text = "네, 물론이지요... 하지만 서면 절차 없이도 충분히 해결할 수 있다고 생각합니다. 그에게 이렇게만 전하십시오. '이 자는 죽어야 한다.' 그것이 공정할 것이고, 받은 사과의 '가치'를 고려하면 아무 문제도 없을 것입니다. 그리고 이 사건은 완전히 종결된 것으로 간주될 것입니다.";
			link.l1 = "좋소, 기억하겠소, 나리. 또 다른 일이라도 있소?";
			link.l1.go = "SantiagoTripBank_4";
			DelLandQuestMark(npchar);
		break;
		
		case "SantiagoTripBank_4":
			dialog.text = "예, 물론입니다. 제가 말한 것은 지랄디 가문의 뜻입니다. 그리고 물론, 루카스 나리께 제 안부를 전해 주셔도 됩니다. 순풍이 함께하길 빕니다, 선장님\n "+GetFullName(pchar)+".";
			link.l1 = "알겠습니다. 안녕히 가십시오, 나리 "+npchar.name+".";
			link.l1.go = "SantiagoTripBank_5";
		break;
		
		case "SantiagoTripBank_5":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "SantiagoTripFinal";
			LAi_LocationDisableOfficersGen("Santiago_town", false);//офицеров пускать // 291112
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
