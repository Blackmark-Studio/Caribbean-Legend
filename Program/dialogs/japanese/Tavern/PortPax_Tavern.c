// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("「すべての噂話は」 "+GetCityName(npchar.city)+" お役に立ちますぜ。何を知りたいんだ？","ちょうどその話をしていたところだぜ。お前、忘れちまったのか……","今日はその質問を持ち出すのはこれで三度目だな……","お前、オウムみたいに同じことばかり繰り返してるじゃねえか…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知ってるか、」 "+NPChar.name+"、また今度だな。","ああ、なぜか忘れちまってたんだ…","「ああ、本当にこれで三度目だな……」","ああ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince")
			{
				link.l1 = "教えてくれ、お前の植民地に最近「サンタ・マルガリータ」って名のガレオン船が寄港したことはあるか？ もしかして私掠船の戦利品としてかもしれねえが？";
                link.l1.go = "guardoftruth";
			}
			//--> Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogCitizen"))
			{
				link.l1 = "最近トリスタン・ルニエがここを通ったか？";
				link.l1.go = "UV_DialogTavern";
			}
			//<-- Украденное воспоминание
		break;
		
		case "guardoftruth":
			dialog.text = "相棒、うちの植民地に戦利品を持って立ち寄る奴なんて滅多にいねえし、その名前のガレオン船も見かけてねえよ。 イスパニョーラは荒っぽい島で、俺たちは小さな植民地さ。ここは静かなもんだぜ。 高地のバッカニアどもと牛の皮や干し肉を取引してるくらいだ。私掠船も普通は長居しねえ、こっちには売春宿もねえし、 スペイン野郎どもも近くにいるからな。自分のガレオン船は他で探しな。";
			link.l1 = "なるほどな。忠告ありがとな！";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "7");
			pchar.questTemp.Guardoftruth = "tortuga";
		break;
		
		//--> Украденное воспоминание
		case "UV_DialogTavern":
			dialog.text = "レニエか？ああ、あいつはここに来ただけじゃねえ、まだここにいるぜ。部屋を取って泊まってるんだ。";
			link.l1 = "運が俺に味方してるぜ！あの立派な船長との用件は一刻を争うんだ――必要にはプライバシーも譲ってもらわなきゃな。どの部屋にいるか教えてくれないか？";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RoomInTavern");
			DelLandQuestMark(npchar);
		break;
		//<-- Украденное воспоминание

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
