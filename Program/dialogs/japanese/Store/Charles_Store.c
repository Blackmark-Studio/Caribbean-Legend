// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("さあ、用件は何だ？","ちょうどその話をしていたところです。あなたは忘れてしまったのでしょう…","今日はもう三度目だぞ、何か質問を持ち込むのは……","聞け、ここは店だ。人はここで物を買うんだ。邪魔するな！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知ってるだろう、」 "+NPChar.name+"、また今度かもしれませんね。","そうだ、なぜか忘れてしまったんだ……","ああ、本当にこれで三度目だな……","ふむ、俺はしない……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.Goods"))
			{
				link.l1 = "お前の倉庫に俺の品物が保管されている。茶、カカオ、それにリグナムバイタだ。引き取りたいんだ。";
                link.l1.go = "patria_goods";
			}
			if (CheckAttribute(pchar, "questTemp.Patria.GoodsSM"))
			{
				link.l2 = "シント・マールテンからの私の品物があなたの倉庫に保管されているはずだ。ノエル・フォルグ男爵が私に託したものだ。 ";
                link.l2.go = "patria_goods_3";
			}
		break;
		
		case "patria_goods":
			dialog.text = "その通りです、船長。ご注文の商品は用意してあります。本当にお受け取りになりますか？";
			link.l1 = "「はい。」";
			link.l1.go = "patria_goods_1";
			link.l2 = "ちょっと待ってくれ、まず船倉に十分な空きがあるか確認しないといけねえ。";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_1":
			dialog.text = "完璧です。荷運び人たちに桟橋まで運ぶよう命じます。";
			link.l1 = "「取引成立！」";
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
			dialog.text = "そう、その通りです。男爵の命令でここに保管しています。本当にお持ちになりますか？";
			link.l1 = "「はい。」";
			link.l1.go = "patria_goods_4";
			link.l2 = "ちょっと待ってくれ、まず船倉に十分な空きがあるか確認しないといけねえ。";
			link.l2.go = "exit";
		break;
		
		case "patria_goods_4":
			dialog.text = "完璧だ。荷運び人たちに桟橋まで運ばせよう。";
			link.l1 = "「取引成立だ！」";
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
