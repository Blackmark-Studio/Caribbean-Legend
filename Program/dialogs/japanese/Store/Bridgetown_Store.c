// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("どうぞ、何のご用ですか？","ちょうどその話をしていたところです。あなたは忘れてしまったのでしょう…","今日はこれで三度目だ、この質問を持ち出すのは……","聞け、ここは店だ。人はここで物を買うんだ。邪魔しないでくれ！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知っているだろう、」 "+NPChar.name+"、また今度かもしれませんね。","そうだ、なぜか忘れてしまった……","ああ、本当にこれで三度目だな……","ふむ、俺はやらない……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "聞いてくれ、ちょっとした噂なんだが、ベリーズではまもなく紅木とカカオの値段が跳ね上がるらしい。 最近いい取引をして、財布もドゥブロンでパンパンさ、へへ…この品をいくらか仕入れたいんだ。割引してもらえるかな？\n";
                link.l1.go = "StoreDone";
            }
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados1")
			{
				link.l1 = "「アドミラーブル」という名のガレオン船が最近、ガイウス・マルシェ船長の指揮であなたの植民地に入港しました。\n彼がここで弾薬や転売用の商品を仕入れた可能性はありますか？";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "StoreDone":
			dialog.text = "そうですね、旦那、もし本当に大量の取引でしたら、もちろん、適切な値引きについてご相談できますよ。";
			link.l1 = "素晴らしい！造船所で新しいフリュートが近日中に売りに出されると聞きました。私はそれを待って、 その船を買うつもりです。自分のブリッグから大砲を全部外したのに、 それでもこの商品全部を積むには船倉が足りません！また後で寄りますね！";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-11");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "はっ！あの変わった男のことは覚えているぞ！ グアドループがバニラを切実に必要とするなんて馬鹿げた噂を信じていたんだ。ヨーロッパの大商人の隊商が立ち寄って、 運べるだけの香辛料を買い漁るとかいう話でな\nそんな戯言は毎月のように耳にするが、マルシェは本気で信じ込んでいた。一週間もここに滞在して、 俺にバニラを船倉いっぱい集めろと頼んできたんだ\n持っていた金を全部それにつぎ込んだらしい。気の毒には思うが、狂気に走る男を止めることは俺にはできんさ。";
			link.l1 = "つまり、今はグアドループにいるかもしれないのか？";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "たぶんそうだろうな。あいつは幻の「商人」どもをキリストの再臨まで待ち続けるつもりだろうし、 バニラを売っても損するだけだ。賢ければ、バニラの需要が急騰するか、 もっと必要とされている場所を確実に見つけるまでバステールに留まるはずだ。";
			link.l1 = "ああ。ありがとう、おかげで大いに助かったぜ！";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "14");
			pchar.questTemp.Guardoftruth = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1 = "location";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1.location = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.function = "GuardOT_CreateTwoShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
