// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("질문, "+GetAddress_Form(NPChar)+"?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("음, 이게 무슨 수작이야, "+GetAddress_Form(NPChar)+"? ","또 이상한 질문이야? 자기야, 가서 럼주라도 한잔해...")+"","오늘 하루 동안 이 질문을 세 번째로 꺼내는군..."+GetSexPhrase(" 이게 애정의 표시인가?","")+"","질문이 더 있나 보군. "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("마음이 바뀌었어","지금은 할 말이 없어."),"아니, 아름답지 않아...","말도 안 돼, 자기야...","아니, 무슨 질문이야?…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "helendrinking":
			dialog.text = "잘 주무셨습니까, 나리? 맥아더 아가씨께서 당신의 완벽한 편안함을 보장하라고 우리에게 명령하셨습니다!";
			link.l1 = "나는 아주 이상한 꿈을 꿨어...";
			link.l1.go = "helendrinking_1";
		break;

		case "helendrinking_1":
			dialog.text = "아!...";
			link.l1 = "무슨 일이신가요, 아가씨? 제가 도와드릴 일이라도 있습니까?";
			link.l1.go = "helendrinking_2";
		break;

		case "helendrinking_2":
			dialog.text = "죄송해요, 선장님... 죄라 해도, 참을 수가 없어요! 제가 많이 서툴지만, 제발 저를 내치지 마세요, 선장님! 너무 멋지세요! 당신을 기쁘게 해주고 싶고, 만지고 싶어요...";
			link.l1 = "정말이지, 완벽하게 편안하군... 너도 아주 아름답네! 이리 와, 부끄러워하지 말고.";
			link.l1.go = "helendrinking_sex";
			link.l2 = "지금은 나를 건드리지 않는 게 좋을 거요, 마드모아젤 – 럼 냄새가 진동하니까. 하지만 나를 기쁘게 해줄 수는 있지 – 아침 식사라면 대환영이오!";
			link.l2.go = "helendrinking_nosex";
		break;
		
		case "helendrinking_sex":
			dialog.text = "이런, 이런!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressSex");
		break;

		case "helendrinking_nosex":
			dialog.text = "무례하군!";
			link.l1 = "아침은 안 먹는 거야?";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressNoSex");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
