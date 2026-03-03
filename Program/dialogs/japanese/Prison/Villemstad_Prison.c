// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "話せ、聞いてやる";
			link.l1 = "俺の勘違いだった。じゃあな。";
			link.l1.go = "Exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalInPrison")
            {
                link.l1 = "役人、ここに「ポルトガルのバルトロメオ」という囚人を拘留しているそうだな…";
                link.l1.go = "Portugal";
            }
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "そうだ。だが、なんでお前が気にするんだ？あいつに会えるのはオランダ西インド会社の使者だけだし、 しかも総督の書面命令が必要だ。今は会社の役人の一人がその海賊を尋問中だ。だから、ただ会いに来ただけなら、 とっとと帰りな。吊るされるときに嫌でも見ることになるぜ。さあ、もう行け。";
			link.l1 = "俺はあいつに会いに来たんじゃねえ。";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "「それでは、なぜですか？」";
			link.l1 = "俺はここに来た……あいつを解放するためにな！";
			link.l1.go = "fight";
			chrDisableReloadToLocation = true;
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
