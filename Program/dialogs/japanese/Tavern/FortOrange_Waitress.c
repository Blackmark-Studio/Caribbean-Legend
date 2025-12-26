// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「質問」 "+GetAddress_Form(NPChar)+"?","どうしたんだ、何か手伝えることがあるか、 "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("ふん、どういうつもりだ、 "+GetAddress_Form(NPChar)+"? ","また変な質問かい？お嬢ちゃん、ラムでも飲んでな。")+"","今日一日で、その質問を持ち出すのはこれで三度目だぞ…"+GetSexPhrase(" これは愛情のしるしか？","")+"","「また質問か、そうだろう。」 "+GetAddress_Form(NPChar)+"?","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった","今は話すことは何もねえぜ。"),"いやいや、美しいお嬢さん…","ありえねえよ、お嬢ちゃん…","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_W")
            {
                link.l1 = "聞けよ、女、あんたは俺の昔の仲間フランソワ・ゴンティエと親しかったって話だぜ。しかも、かなりな……";
                link.l1.go = "Jamaica_ratW_1";
            }
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_WP")
            {
				if (CheckCharacterItem(pchar, "jewelry43"))
				{
					link.l1 = "宝石付きのネックレスを持ってきたぜ。ほらよ。 これからはあんたみたいに欲深い女には神様に守ってもらいたいもんだな。";
					link.l1.go = "Jamaica_ratW_5";
				}
				else
				{
					link.l1 = "今のところ何もない。お前の首飾りを探してるんだ。";
					link.l1.go = "exit";
				}
            }
			
		break;
		
		case "Jamaica_ratW_1":
            dialog.text = "ああ、そうよ。だから何？あたしは人妻じゃないし、好きな人と時間を過ごすわ。フランソワはとても立派な船乗りよ、 地元の漁師や農夫とは違うの。彼は本当に……あっ！それに、素敵な贈り物もくれたのよ！";
            link.l1 = "よし、もういい！俺の仲間がどんな奴かは分かってるから、いちいち説明しなくていい。 お前らの間に何があったかなんて興味ねえし、結婚しようが知ったこっちゃねえ。とにかく、 今すぐあいつを探さなきゃならねえんだ、分かったか？どこへ行ったか知ってるか？";
            link.l1.go = "Jamaica_ratW_2";
        break;
		
		case "Jamaica_ratW_2":
            dialog.text = "ふふっ……あんたはあいつの仲間なのに、どこへ行ったか知らねえのか。おかしいじゃねえか！";
            link.l1 = "笑いごとじゃねえぞ、女。俺たちはジャマイカで落ち合うって約束してたんだ、 それから一緒に航海に出る予定だったんだよ…わかるだろう？俺一人じゃ無理だし、あいつはどこへ行ったのかもわからねえ！";
            link.l1.go = "Jamaica_ratW_3";
        break;
		
		case "Jamaica_ratW_3":
            dialog.text = "なるほどな。まあ、そんな儲かる航海が控えてるってんなら、しかもお前とフランソワは友達だろ…どこへ向かったか教えてやるよ、ただしちょっとした礼が欲しいがな。";
            link.l1 = "ああ、事情はわかってるぜ。いくら欲しいんだ？";
            link.l1.go = "Jamaica_ratW_4";
        break;
		
		case "Jamaica_ratW_4":
            dialog.text = "ああ、なんて欲深いんだ！金なんていらないよ。いや、特別なものが欲しいんだ。 フランソワが宝石付きの素敵なネックレスをくれるって約束してくれたんだ。もう友達に自慢しちゃったし、 あいつはそのままどこかへ行っちまった……そのペンダントを持ってきてくれたら、あいつがどこへ行ったか教えてやるよ、へへっ！";
            link.l1 = "この生意気なあばずれめ！オランダ女は欲深いにもほどがあるぜ！よしよし、首飾りはやるよ。";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_5");
			pchar.questTemp.Slavetrader = "FindRatJamaica_WP";
        break;
		
		case "Jamaica_ratW_5":
            dialog.text = "ああ、美しい！これで仲間たちは羨ましがって緑色になっちまうぜ！";
            link.l1 = "奴らにお悔やみを伝えてくれ。さあ、話を始めろ。フランソワはどこへ向かったんだ？";
            link.l1.go = "Jamaica_ratW_6";
			RemoveItems(PChar, "jewelry43", 1);
        break;
		
		case "Jamaica_ratW_6":
            dialog.text = "ああ、もちろんだ、旦那。フランソワはキューバのハバナへ向けて出航したぜ。";
            link.l1 = "高い情報料ありがとな、姐さん。欲しかったのはそれだけだ。";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_6");
			pchar.questTemp.Slavetrader = "FindRatHavana";
        break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
