// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "話せ、聞いてやる";
			link.l1 = "俺が間違ってた。さらばだ。";
			link.l1.go = "Exit";
			//искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = "ここにサイモン・モレルを拘留しているな。あいつは密輸業者で、つい最近哨戒船にスクーナーを沈められたんだ。 面会させてもらえるか？";
                link.l1.go = "BarbTemptation";
				DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
			{
				link.l1 = "役人殿、俺はフィリップスバーグの旦那総督にここへ送られてきたんだ。あの方から、 イギリスの間者を探すためにこの島と周辺海域を捜索するよう命じられている。閣下は、 あんたが役立つ情報を提供できるともおっしゃっていたぜ。";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
			{
				link.l1 = "役人、行方不明だった巡回隊を見つけたぜ。さらにイギリスの間者も見つけた。奴らはこの島にいるんだ。";
				link.l1.go = "FMQN_3";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_peace_rew")
			{
				link.l1 = "また俺だ、役人。スパイどもを拘束したのか？";
				link.l1.go = "FMQN_8";
			}
		break;
		
		//искушение барбазона
		case "BarbTemptation":
			dialog.text = "「で、あいつが何のために必要なんだ、旦那？」";
			link.l1 = "あいつに「てめえはくそったれのろくでなしだ」と伝えてやりてえんだ。絞首台に立つとき、少しは役に立つといいがな。 ";
			link.l1.go = "BarbTemptation_1";
		break;
		
		case "BarbTemptation_1":
			dialog.text = "ははっ！旦那、なかなかユーモアがあるじゃねえか……まあ、二千ペソ払えば通してやるよ。";
			if(sti(Pchar.money) >= 2000)
			{
				link.l1 = "受け取れ、役人。ありがとう！";
				link.l1.go = "BarbTemptation_2";
			}
			link.l2 = "ふん…やっぱり気が変わったぜ。酒場で金を無駄にしたほうがマシだな。";
			link.l2.go = "BarbTemptation_4";
		break;
		
		case "BarbTemptation_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "どういたしまして……さっさと行け！";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "BarbTemptation_4":
			dialog.text = "ご希望通りにしよう。次はこんな申し出はないぜ。";
			link.l1 = "どうせ俺には必要ねえさ。じゃあな、役人！";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "役に立つ？はっ！……いや、待てよ。お前に伝えておくべき有益な情報がひとつある。 うちの巡回隊の一つがジャングルで行方不明になったんだ。本来ならもう兵舎に戻っているはずだが、 どうやらオウムと遊ぶほうが気に入ったらしい。……いや、本当に何かあったのかもしれん。もし捜索中に奴らを見つけたら、 遅れた理由をまともに説明するように伝えてくれ。さもないと、痛い目を見ることになる……巡回隊の指揮官はヤンネス・ホフマンという名だ。";
			link.l1 = "それだけか、役人？";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "ああ、くそったれ。悪いが、もう話すことはねえんだ。幸運を祈るぜ、船長。";
			link.l1 = "ありがとうございます…";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			DialogExit();
			pchar.questTemp.FMQN = "way_div_1";
			AddQuestRecord("FMQ_Nevis", "10");
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_3":
			DelLandQuestMark(npchar);
			dialog.text = "何だと！？冗談じゃねえだろうな。報告しろ！";
			link.l1 = "ジャングルの洞窟近くで巡回隊に会ったんだ。奴らは俺を止めて、どこへ行くのか、何のためかを聞いてきたが、 その後は行かせてくれた。くそっ、あれがオランダ軍の制服を着たイギリス野郎どもじゃなかったら俺が馬鹿だぜ！ それに、ジャングルで妙なものも見た。まるで裸の男どもが茂みに隠れてるようだった。たぶん、 イギリスの襲撃隊があんたの巡回隊を武装解除して、制服を奪ったんだろうな。";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			dialog.text = "...";
			link.l1 = "ご理解いただけると思うが、訓練された赤服どもの部隊と戦う危険は冒さず、代わりに急いで報告しに来たんだ。";
			link.l1.go = "FMQN_5";
		break;
		
		case "FMQN_5":
			dialog.text = "ほうほう……洞窟だと？何人見かけたんだ？";
			link.l1 = "五人だ。そして、ああ、あいつらはあの洞窟に入っていったと思うぜ。";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			dialog.text = "すぐに洞窟へ部隊を派遣する！船長、もしお前が会った連中が本当にイギリスのスパイなら、相応の報酬をやるぞ。 もし当局の逮捕に協力してあの野郎どもを捕まえ、追加の報酬が欲しいなら、部隊に同行しても構わん。 これは総督の命令だ。さて、一緒に来るか？\n";
			link.l1 = "いや、役人、スパイを追うのはお前の仕事だ。しっかり武装した部隊を送れよ、あいつらは危険すぎるからな…";
			link.l1.go = "FMQN_7";
			link.l2 = "できそうだな。俺が手伝えば、お前の部下たちもスパイをもっと早く見つけられるだろう。";
			link.l2.go = "FMQN_10";
		break;
		
		case "FMQN_7":
			dialog.text = "お前の選択だ、船長。お前の助言は考慮しておくぜ。作戦の結果を聞きたけりゃ、明日また俺のところに来な。";
			link.l1 = "また明日会おう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeace");
		break;
		
		case "FMQN_8":
			DelLandQuestMark(npchar);
			dialog.text = "情報は正しかったぞ、船長。あの野郎どもは洞窟の中にいた。降伏する気はまったくなく、戦いを仕掛けてきた。 結果として、全員始末したぜ。行方不明だった巡回隊も見つけた。少しやられてはいたが、無事生きている……ありがとう、船長。フィリップスバーグの善良な市民を代表して礼を言う。約束通り、お前の警戒心には報酬を与えよう。 さあ、受け取ってくれ。";
			link.l1 = "ありがとう！";
			link.l1.go = "FMQN_9";
		break;
		
		case "FMQN_9":
			AddMoneyToCharacter(pchar, 10000);
			dialog.text = "シント・マールテンではいつでも歓迎する客人だ。さて、失礼する。他に用事があるのでな。";
			link.l1 = "俺もだ。じゃあな。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeaceComplete");
		break;
		
		case "FMQN_10":
			dialog.text = "よろしい。助力に感謝する。市門へ行け、懲罰隊は一時間後にそこへ集結するぞ。";
			link.l1 = "一つ忠告しておく。この任務にはお前が持っている中で一番腕の立つ兵士を送った方がいいぜ。 あいつらスパイは危険だからな。";
			link.l1.go = "FMQN_11";
		break;
		
		case "FMQN_11":
			dialog.text = "心配するな。フィリップスブルク一の剣士、ハンス・シュルテ士官の指揮の下、最も経験豊富な兵士たちを送る。";
			link.l1 = "よし！じゃあ、時間を無駄にせずに行こうぜ。";
			link.l1.go = "exit";
			WaitDate("",0,0,0,1,5);
			AddDialogExitQuestFunction("FMQN_HollandBattle");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
