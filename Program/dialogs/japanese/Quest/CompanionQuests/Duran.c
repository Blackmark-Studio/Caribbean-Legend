void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "何でもねえ。";
			link.l1.go = "exit";
		break;
		
		case "SKD_DomAnri":
			dialog.text = "俺の家へようこそ、旦那方。何かご用かい？";
			link.l1 = "ルヴァスールがよろしくと言ってたぜ、旦那。";
			link.l1.go = "SKD_DomAnri_2";
			StartQuestMovie(true, false, true);
		break;
		
		case "SKD_DomAnri_2":
			dialog.text = "そういうことか……アリシア！ちょっと席を外してくれ。こいつらは俺と用があるんだ。";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_2_1";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		case "SKD_DomAnri_2_1":
			StartInstantDialog("SKD_Alisia", "SKD_DomAnri_3", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_3":
			dialog.text = "しかし…";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_3_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
		break;
		case "SKD_DomAnri_3_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_4", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_4":
			dialog.text = "愛してるぜ、ダーリン。さあ、行けよ！";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_5";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		
		case "SKD_DomAnri_5":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Anri_DlgExit_1");
		break;
		
		case "SKD_DomAnri_6":
			dialog.text = "なんと素晴らしい御業だ、主よ！人生のすべてを失っても、世界の果てで愛する人に出会えたのなら、それだけで十分だ！ \n諸君、俺はもうお前たちのものだぜ。さて、取引の話でもできるかね？";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_6_1";
		break;
		case "SKD_DomAnri_6_1":
			StartInstantDialog("Duran", "SKD_DomAnri_7", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_7":
			dialog.text = "いや、情けを乞うのもやめとけよ。";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_7_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
			locCameraFromToPos(-0.52, 1.47, 0.76, false, -2.52, 0.20, 0.99);
		break;
		case "SKD_DomAnri_7_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_8", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_8":
			dialog.text = "騎士団の騎士が慈悲を乞うなんて、似合わねえよ。";
			link.l1 = "元騎士だったけどな。";
			link.l1.go = "SKD_DomAnri_9";
		break;
		
		case "SKD_DomAnri_9":
			dialog.text = "役人どもがどれだけインクを持っていようが、その称号を俺から奪うことはできねえさ。";
			link.l1 = "その場合は、証明してみせろ。だがまずは俺の好奇心を満たしてくれ。お前は王冠への裏切り者か？そうでなきゃ、 なぜルヴァスールがそこまでお前の命を狙ったのか理解できねえんだが。";
			link.l1.go = "SKD_DomAnri_10";
		break;
		
		case "SKD_DomAnri_10":
			dialog.text = "俺は自分の誓いに忠実だ、旦那、だからそのことで俺を責めないでくれ。\nただ言えるのは、王冠に背いた裏切り者が、別の裏切り者を始末するために俺を送り込んだってことだけだ。\nそして、俺より腕の立つ仲間が成功するまで、奴は何度でも同じことを繰り返すだろう。\nもう話は十分だ。諸君、戦闘だ！";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_11";
		break;
		
		case "SKD_DomAnri_11":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Anri_DlgExit_2");
		break;
		
		case "SKD_DomAnri_12":
			dialog.text = "ああっ！おお、ありがとうよ、船長。あいつは手強い野郎だったぜ。俺一人じゃ絶対に勝てなかったさ。";
			link.l1 = "どうもこの勝利はあまり嬉しくねえな。もうここで用は済んだか？";
			link.l1.go = "SKD_DomAnri_13";
		break;
		
		case "SKD_DomAnri_13":
			dialog.text = "まだだ、まずはさっさと二階に逃げたあの娘を片付けて始末しねえとな。";
			link.l1 = "「何だと！？やめろ！正気か、クロード？俺は人斬りじゃねえぞ！」";
			link.l1.go = "SKD_DomAnri_14";
		break;
		
		case "SKD_DomAnri_14":
			dialog.text = "何もしなくていいぜ、船長。\nそれに、全部お前のせいだろ。あいつにルヴァスールのことなんか話すんじゃなかったんだよ。";
			link.l1 = "そんなのはでたらめだって、あんたも分かってるだろ。\nそれに、また意味不明な小言を言ってみろ、今度はただじゃ済まさねえからな。";
			link.l1.go = "SKD_DomAnri_15";
		break;
		
		case "SKD_DomAnri_15":
			dialog.text = "へっ！悪いな、船長。確かに、ルヴァスールの命令には騎士だけじゃなく、 その仲間全員を始末しろってはっきり書いてあったんだ。全員だぜ、わかるか？あいつらは甘く見ちゃいけねえし、 要求も真剣に受け止めるべきだ。俺の仕事の邪魔はしないでくれよ、船長。あと一つだけ汚れ仕事を片付けたら、 今度こそ最後まであんたに付き合うって誓うぜ！\n";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				Notification_Reputation(true, 71, "low");
				Notification_Perk(true, "Trustworthy");
				link.l1 = "（信頼）（名誉）あんたは昔、俺が大きく羽ばたく運命だと言って、 そのために力を貸せるのが嬉しいとも言ってくれたな。";
				link.l1.go = "SKD_DomAnri_VD";
			}
			else
			{
				if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
			}
			link.l2 = "くたばりやがれ！汚れ仕事は自分でやれ。お前の誓いは受け取ったぜ、命懸けで守るんだな。本当に分かってるか？";
			link.l2.go = "SKD_DomAnri_DuranDruzhba";
			link.l3 = "この値段じゃ無理だ、クロード。あの娘を殺させるわけにはいかない。";
			link.l3.go = "SKD_DomAnri_DuranDraka";
		break;
		
		case "SKD_DomAnri_DuranDraka":
			dialog.text = "へっ！俺たちは最初から殺し合う運命だったってことか、船長？";
			link.l1 = "まあ、そうだな。トルトゥーガで中断したところから再開しようぜ、どうだ？";
			link.l1.go = "SKD_DomAnri_DuranDraka_2";
		break;
		
		case "SKD_DomAnri_DuranDraka_2":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_3");
		break;
		
		case "SKD_DomAnri_DuranDruzhba":
			dialog.text = "了解だ、船長！";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_2";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_2":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_4");
		break;
		
		case "SKD_DomAnri_DuranDruzhba_3":
			dialog.text = "終わったぜ、船長。あいつにはちょっと驚かされたな…";
			link.l1 = "その話は聞きたくねえ。俺は約束を守ったぜ。今度はお前の番だ。";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_4";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_4":
			dialog.text = "金は大事だが、ただの傭兵のために自分の命を張るなんて、それ以上の価値があるぜ。最後まで一緒にいるぜ、船長。";
			link.l1 = "その場合は、ここでおしまいだな。";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_5";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_5":
			dialog.text = "あいよ。";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_6";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_6":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_5");
		break;
		
		case "SKD_DomAnri_VD":
			dialog.text = "やったぜ。それがどうした、船長？";
			link.l1 = "その言葉がただの戯言じゃないって証明してみせろ。俺の仲間になりたいのか？これからの分け前が欲しいのか？ だったら俺の命令に従え。女には手を出すな。なぜかって？そうしなけりゃ、いつまでもただの人斬りのままだし、 そんな奴の居場所は俺の中にはねえからだ。";
			link.l1.go = "SKD_DomAnri_VD_2";
		break;
		
		case "SKD_DomAnri_VD_2":
			dialog.text = "これで二度目だな、俺とお前が命を懸けて戦うのは、船長\nそしてまたしても、お前の口のうまさで勝ちやがったな！ははっ！言ってやがった通りだ！まあ、 女なんざくたばっちまえ。どうせ俺は獣みてえなもんだ。乗組員に加えてもらっていいか？";
			link.l1 = "ようこそ、クロード。今度こそ本当に歓迎するぜ。";
			link.l1.go = "SKD_DomAnri_VD_3";
		break;
		
		case "SKD_DomAnri_VD_3":
			dialog.text = "あいよ、船長！";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_VD_4";
		break;
		
		case "SKD_DomAnri_VD_4":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_6");
		break;
		
		case "SKD_KlodDuran":
			dialog.text = "ちょっとした用事ができたんだ、船長。";
			Link.l1 = "またどうせ「辞める」って脅して、給料を上げろって言うつもりだろ？";
			Link.l1.go = "SKD_KlodDuran_1";
		break;
		
		case "SKD_KlodDuran_1":
			dialog.text = "へっ！今回は違うぜ……心配すんな、船長。ちゃんと報酬さえくれりゃ、俺はあんたのもんだ……まあ、常識の範囲内でな。俺たち傭兵仲間が生き残るには、それしかねえんだよ。しかも、 腕利きですら雀の涙ほどしかもらえねえんだぜ。";
			link.l1 = "さっさと本題に入ろうじゃねえか？";
			link.l1.go = "SKD_KlodDuran_2";
		break;
		
		case "SKD_KlodDuran_2":
			dialog.text = "トルトゥーガのあの女を覚えてるか？";
			link.l1 = "マルセリーヌ？総督の奥方か？あんな女、忘れられるわけがねえだろ。";
			link.l1.go = "SKD_KlodDuran_3";
		break;
		
		case "SKD_KlodDuran_3":
			dialog.text = "俺がルヴァスールの家に来たのは偶然じゃねえ。あのろくでなしで異端者とは、ちょっとした因縁があったんだ。";
			link.l1 = "「権力者をそんなにけなすなんて、ちょっと変わってるじゃねえか、クロード。」";
			link.l1.go = "SKD_KlodDuran_4";
		break;
		
		case "SKD_KlodDuran_4":
			dialog.text = "ん？へっ！ルヴァスールは悪魔だぜ！あいつは、あいつに群がる海賊どもよりもよっぽどタチが悪いんだ！";
			link.l1 = "お前自身があいつと取引したって言ったばかりじゃねえか。ちょっと偽善的じゃねえのか？";
			link.l1.go = "SKD_KlodDuran_5";
		break;
		
		case "SKD_KlodDuran_5":
			dialog.text = "俺は聖人じゃねえよ、船長。言われた相手を殺して食ってるだけさ。だからこそ、あんたは俺を重宝してるんだろ？\nだがな、俺みたいな奴でも、トルトゥーガのルヴァスールの巣で女たちに何をしてるかって噂を聞くと、ぞっとするぜ！";
			link.l1 = "噂話には興味ねえよ。この男は貴族であり、国王に仕える者だ。敬意を払うべきだぜ。";
			link.l1.go = "SKD_KlodDuran_6";
		break;
		
		case "SKD_KlodDuran_6":
			dialog.text = "つまり、あんたは王様の家来をぶんどって、その嫁さんまで寝取ったってわけか？へっ！好きにしな、船長。\nさて、本題に入ろうぜ。閣下から「ある男を探して殺せ」と命じられたんだ。まあ、よくある仕事さ。 こんな偉いお方から、しかも直々に頼まれることは滅多にねえがな。";
			link.l1 = "で、何が望みだ？お前を解放して、この男を殺すって約束を果たさせろってのか？";
			link.l1.go = "SKD_KlodDuran_7";
		break;
		
		case "SKD_KlodDuran_7":
			dialog.text = "手伝ってほしいんだ、船長。トルトゥーガで俺の身が危なくなったとき、お前の下につくことにしたが、 この仕事を終わらせるまでは落ち着けねえ。ルヴァスールにバレたら殺されちまうしな。それに、 仕事を途中で投げ出すのはプロ失格だぜ。";
			link.l1 = "依頼人の妻と関係を持つのがプロらしいか？そんな頼みを旦那から聞くとは妙な話だな、 とくに俺たちの関係について最初に旦那が言い当てたことを思い出すとな。金のために血を流す、 それが俺たちの本質じゃねえか？";
			link.l1.go = "SKD_KlodDuran_8";
		break;
		
		case "SKD_KlodDuran_8":
			dialog.text = "俺を助けてくれたら、剣だけじゃなくて忠誠も捧げるぜ。あんたが大物になる運命だってのは一目でわかる、船長。 俺もその手助けができりゃ嬉しいもんさ。";
			link.l1 = "正直に言うと、あんたみたいな腕の立つ奴に背中を預けたいもんだぜ。で、その標的はどこにいるんだ？";
			link.l1.go = "SKD_KlodDuran_10";
			link.l2 = "今はそのサーベルで十分だ。俺は暗殺者じゃねえ。落ち着け、士官！";
			link.l2.go = "SKD_KlodDuran_9";
		break;
		
		case "SKD_KlodDuran_9":
			dialog.text = "あいよ、船長。聞いてみる価値はあったぜ。";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_9_1";
		break;
		
		case "SKD_KlodDuran_9_1":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_1");
		break;
		
		case "SKD_KlodDuran_10":
			dialog.text = "へっ！そこが問題なんだよ、船長。俺が知ってるのは、そいつがマルタ騎士団の元騎士で、 どこかイギリス領内を逃げ回ってるってことだけさ。貴族の生まれだから、ボロ小屋なんかに住んじゃいねえだろうな。";
			link.l1 = "「騎士団の騎士か？」";
			link.l1.go = "SKD_KlodDuran_11";
		break;
		
		case "SKD_KlodDuran_11":
			dialog.text = "元騎士だ。ああ、この仕事を引き受けたことはもう千回は後悔してるぜ。騎士ってのは悪魔みたいに戦うからな、 剣の腕が本当に試されるぜ、保証するよ。";
			link.l1 = "気に入らねえが、やってみるか。さて――貧乏人じゃなくて、貴族で、しかもイギリス人と一緒に隠れてるって？ルヴァスールは、 そいつを始末しろって理由は言わなかったのか？";
			link.l1.go = "SKD_KlodDuran_12";
		break;
		
		case "SKD_KlodDuran_12":
			dialog.text = "もちろん来やしねえさ！だが、どう見ても政治的な話だぜ。そうじゃなきゃ兵隊を送り込んでるはずだ。";
			link.l1 = "やってみるが、約束はできねえぜ。";
			link.l1.go = "SKD_KlodDuran_13";
		break;
		
		case "SKD_KlodDuran_13":
			dialog.text = "「ありがとな、船長。」";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_14";
		break;
		
		case "SKD_KlodDuran_14":
			DialogExit();
			AddDialogExitQuestFunction("Duran_Duran_DlgExit_2");
		break;
		
	}
} 
