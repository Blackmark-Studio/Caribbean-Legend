// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("모든 소문에 대해 "+GetCityName(npchar.city)+" 명령만 내리십시오. 무엇을 알고 싶으신가요?","우리가 막 그 얘기하고 있었어. 네가 잊어버린 모양이군...","이제 세 번째로 나를 귀찮게 하는군...","너, 앵무새처럼 똑같은 말만 반복하고 있잖아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 아마 다음에.","그래, 뭔가 이유가 있었는지 내가 잊어버렸군...","그래, 정말 이번이 세 번째야...","그래...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && !CheckAttribute(npchar, "quest.gonsales"))
			{
				link.l1 = "엔리케 곤살레스를 찾고 있어. 어떻게 찾아야 하는지 알려줄 수 있나?";
				link.l1.go = "saga";				
			}
		break;
			
		case "saga":
			dialog.text = "누구나 곤살레스 나리를 알지! 그의 집은 항만청 바로 옆에 있어.";
			link.l1 = "그 사람 몇 살이야?";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "글쎄, 확실히 말할 순 없지만, 적어도 쉰 살은 넘어 보이네. 그 집에서 꽤 오래 살았지. 해적들에 관한 온갖 허풍스러운 이야기를 늘어놓는 걸 좋아하는데, 아마 꿈에서나 만난 놈들 얘기일 거야.";
			link.l1 = "내가 찾던 사람이 저 사람이군. 고맙다, "+npchar.name+", 정말 큰 도움이 되었어!";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			DialogExit();
			npchar.quest.gonsales = "true";
			pchar.questTemp.Saga.Gonsales = "true";
			pchar.quest.Saga_Gonsales1.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales1.win_condition.l1.location = "Cartahena_houseF2";
			pchar.quest.Saga_Gonsales1.function = "Saga_CreateGonsalesA";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
