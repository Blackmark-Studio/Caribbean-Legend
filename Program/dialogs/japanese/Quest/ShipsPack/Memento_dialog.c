void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			link.l1 = "「何もない。」";
			link.l1.go = "exit";
		break;
		
		// Диалог с Алонсо после успешного абордажа
		case "Memento_MortimerGrimDead_Alonso_1":
			dialog.text = "船長、今日は俺たちの勝ちだぜ。先陣が下層デッキの掃討を終わらせてる。捕虜はなし……ははっ！あんたも手加減しなかったみてえだな。";
			link.l1 = "なぜか壮大な演説でもあるのかと思ってたが、奴はただ突っ込んできただけだった。";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_2";
			Achievment_Set("ach_CL_154");
			if (sti(pchar.rank) <= 11) Achievment_Set("ach_CL_156");
		break;

		case "Memento_MortimerGrimDead_Alonso_2":
			dialog.text = "「率直に話してもいいか？」";
			link.l1 = "承知した。";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_3";
			link.l2 = "いや、ここはもう終わりだ。";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_3":
			dialog.text = "なぜ俺たちはあいつらを襲ったんだ？あのブリッグは脅威じゃなかったし、積み荷もなかった。 確かにグリムについてはいろんな噂があったが、奴を恐れていたのは奴隷商人くらいだ。今日は多くの人間が死んだ――それが一体何のためだったんだ？";
			if (sti(pchar.questTemp.ISawDiegoDeLanda) >= 2)
			{
				link.l1 = "...";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_4";
			}
			else
			{
				link.l1 = "今はお前が船員たちの代表ってわけか？";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
			}
		break;

		case "Memento_MortimerGrimDead_Alonso_4":
			dialog.text = "……そしてこれが初めてじゃねえ……";
			link.l1 = "今はお前が乗組員を代表して話してるのか？";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_5":
			dialog.text = "いや、違うぜ。もし船員たちがそんな疑問を持ったら、俺の仕事ぶりが悪いってことだし、 お前はもう死んだも同然だろうな\n"+
			"運が良かったな、野郎どもはこの血まみれの冒険でしっかり儲けたぜ。この船の船乗りはみんな、 ポケットにドブロン金貨をぎっしり詰め込んでやがった！\n"+
			"だが、貴重な積み荷はなかった――ただの土着の装飾品や不気味なお守りばかりだ。それでも、乗組員たちはまるで盗賊のように儲けたぜ。 グリムがしっかり報酬を払ったらしい\n"+
			"その金の分け前をもらおうなんて考えてねえだろうな、船長？";
			link.l1 = "俺じゃねえよ、アロンソ。知らせてくれてありがとうな。";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_6";
			link.l2 = "そうだ。俺の取り分はちゃんと船室に届けておけよ。";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_7";
		break;

		case "Memento_MortimerGrimDead_Alonso_6":
			dialog.text = "いつでもあんたの味方だぜ、船長。\nところで、そのメメントをどうするつもりなんだ？";
			link.l1 = "戦利品としていただく――他に何があるんだ？";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "未決定"+GetSexPhrase(""," まだ")+" .";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
		break;

		case "Memento_MortimerGrimDead_Alonso_7":
			dialog.text = "いつでもあんたの味方だぜ、船長。ところで、そのメメントをどうするつもりなんだ？";
			link.l1 = "戦利品としていただく――他に何がある？";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "未決定"+GetSexPhrase(""," まだ")+" .";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
			AddCrewMorale(Pchar, -10);
			AddItems(Pchar, "gold_dublon", 500);
		break;

		case "Memento_MortimerGrimDead_Alonso_8":
			dialog.text = "やめておいたほうがいいぜ。何か土着の記号で覆われてるしな。それに悪い噂もある――かつて恐ろしい疫病を生き延びて、甲板が死体で踊るようだったって話だ\n"+
			"船尾の骸骨については、俺は近づきもしねえよ。誰かバカが面白半分で頭蓋骨を奪おうとでもしない限り、 俺以外にあそこで見張りをする奴なんていねえんだ。";
			link.l1 = "了解だ、Alonso。仕事に戻るぞ。";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_9";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_9":
			dialog.text = "ああ、船長。";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_end";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_end":
			DialogExit();
			AddDialogExitQuestFunction("Memento_MortimerGrimDead_Alonso_2");
		break;
		
		// Диалог с Алонсо в первую ночь
		case "Memento_Dich_EtapOne_Alonso_1":
			dialog.text = "船長、こんな時間にお邪魔してすまねえ。";
			link.l1 = "「報告しろ、アロンソ。」";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_2";
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapTwo"))
			{
				dialog.text = "船長？こんなところで何してるんだ？ここで寝てたのか？";
				link.l1 = "関係ねえ。";
				link.l1.go = "Memento_Dich_EtapTwo_Alonso_2";
				link.l2 = "俺の船室、なんだか…落ち着かねえな。";
				link.l2.go = "Memento_Dich_EtapTwo_Alonso_2";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_2":
			dialog.text = "状況は最悪だ。乗組員の士気は地に落ちてる！船が呪われてるって公然と言い出す奴までいる。 夜になると何かを見たって文句ばかりだ。";
			link.l1 = "「何を見てるって？」";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_3";
		break;

		case "Memento_Dich_EtapOne_Alonso_3":
			dialog.text = "悪夢ばかりさ。だが一番きついのは、仲間の一人が熱病で死んじまったことだ。若くて牛みたいに丈夫な奴だったのに、 数時間で焼けるように熱を出して逝っちまったんだ。";
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				link.l1 = "それは医者が決めることだ。 "+sld.name+" 腕は確かだ。";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
			else
			{
				link.l1 = "それは普通じゃねえ。乗組員をしっかりまとめておけ、アロンソ。それがお前の仕事だ。";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
		break;
		
		case "Memento_Dich_EtapOne_Alonso_4":
			dialog.text = "あいよ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapOne_End");
		break;
		
		// Диалог с Алонсо во вторую ночь
		case "Memento_Dich_EtapTwo_Alonso_2":
			dialog.text = "わかった。今じゃ乗組員の多くが、怖がって一人になるのを避けて、集まって寝てるんだ。\nこの船で一人きりになるなんて、そもそも無理な話なのにな……";
			link.l1 = "うまくいかなかったみたいだな。何があったんだ？";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_3";
		break;

		case "Memento_Dich_EtapTwo_Alonso_3":
			dialog.text = "喧嘩があった――ホセがマルセルを刺した。やつは「疫病を持ってる」と叫んでいた。";
			link.l1 = "状況は悪化しているのか？";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_4";
		break;

		case "Memento_Dich_EtapTwo_Alonso_4":
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				dialog.text = sld.name+" 今朝すでに報告しました。十一人の仲間を失いました。どうすればいいんだ？";
			}
			else
			{
				dialog.text = "さらに十一人の命が失われた。どうするつもりだ？";
			}
			link.l1 = "俺が呼ぶぜ。";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_5";
		break;

		case "Memento_Dich_EtapTwo_Alonso_5":
			dialog.text = "そうだといいがな、船長。で、ホセはどうする？殺しってのは冗談じゃ済まねえぞ。";
			link.l1 = "鐘が鳴った後であいつを吊るせ。俺たちが支配してるって見せてやるんだ。";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_6";
			link.l2 = "三十回の鞭打ちだ。生き残れば――それが神の御心だ。";
			link.l2.go = "Memento_Dich_EtapTwo_Alonso_7";
		break;

		case "Memento_Dich_EtapTwo_Alonso_6":
			dialog.text = "あいよ！";
			link.l1 = "...";
			link.l1.go = "exit";
			SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 1);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;

		case "Memento_Dich_EtapTwo_Alonso_7":
			dialog.text = "あいよ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddCrewMorale(Pchar, -10);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;
		
		// Диалог с Алонсо в третью ночь
		case "Memento_Dich_EtapThree_AlonsoPrizrak_1":
			dialog.text = "船長！警報だ！！すぐに砲甲板へ行かないといけません！";
			link.l1 = "「何が起きてるんだ？」";
			link.l1.go = "Memento_Dich_EtapThree_AlonsoPrizrak_2";
		break;

		case "Memento_Dich_EtapThree_AlonsoPrizrak_2":
			dialog.text = "自分の目で確かめたほうがいいぜ。さあ、急げ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_4_1");
		break;
		
		// Уже утром
		case "Memento_Dich_EtapThree_Alonso_1":
			dialog.text = "おはよう、船長！";
			link.l1 = "「はっ！？」";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_2";
		break;

		case "Memento_Dich_EtapThree_Alonso_2":
			dialog.text = "うわ、お前ひどい顔してるな。昨夜は荒れたのか？まあ、いい知らせがあるぜ。疫病は終わった。実は——最初からそんなもん無かったんだよ。";
			link.l1 = "どういう意味だ？";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_3";
		break;

		case "Memento_Dich_EtapThree_Alonso_3":
			dialog.text = "乗組員たちはビビっちまって、くだらねえ幽霊船の噂を信じ始めたんだ。暗示の力ってのは恐ろしいもんだぜ。実際、 それで沈んだ船は一隻や二隻じゃねえ。";
			link.l1 = "「でも人が死んだんだ！」";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_4";
		break;

		case "Memento_Dich_EtapThree_Alonso_4":
			dialog.text = "戦い、汚れた傷、腐った塩漬け肉――これが普通の船乗りの計算だ。呪われた船の噂で自分たちを煽り立てなけりゃ、 もう少し犠牲は少なかったかもしれねえな\n"+
			"船尾の骸骨は役に立たなかったな。まあ、誰かの悪戯で夜のうちに帽子が盗まれたのは幸いだったぜ\n"+
			"そんな冒涜をしても雷に打たれなかったから、船員たちは元気を取り戻し、船乗りらしい悪知恵を働かせ始めたんだ。 例えば……\n";
			link.l1 = "骸骨に触るな！";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_5";
		break;

		case "Memento_Dich_EtapThree_Alonso_5":
			dialog.text = "えっと…まあ、気に入ったんなら、もちろん俺たちはやらねえよ。良い一日をな、船長\n"+
			"ところで、いい帽子だな！お前によく似合ってるぜ。前の持ち主には合わなかったみたいだな。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_End");
		break;
		
		// Диалоги с командой Мементо
		case "Memento_Sailor_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "ごきげんよう、船長。グリム船長に話をしたほうがいいぞ。";
				link.l1 = "悪いな、水夫、だがここじゃお前は目立ってるぜ。";
				link.l1.go = "Memento_Sailor_1_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "他に何かあるか、船長？";
				link.l1 = "「何もない。」";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_1_1":
			dialog.text = "言いたいことは分かるぜ、船長。俺も自由船長の下で働いてた――あんたみたいなやつさ。そいつは財宝を追い、交易し、貨物も運んでた。だが、ある日商人どもを襲うと決めてな……うまくいかなかった。生き残った連中は海賊として絞首刑を言い渡されたよ。";
			link.l1 = "「それでグリム船長があんたを買ったのか？」";
			link.l1.go = "Memento_Sailor_1_2";
		break;

		case "Memento_Sailor_1_2":
			dialog.text = "俺たち全員をまとめて一括で買いやがった、まるで貨物みてえにな。どんな船にも経験豊富な水夫が必要だが、 グリムは酒場で人を集めたりしねえ……だが、飯は食わせてくれるし、給金も悪くねえ。だから俺たちは仕える――そしてくじ引きで運命を決めるんだ。";
			link.l1 = "くじ引きか？";
			link.l1.go = "Memento_Sailor_1_3";
		break;

		case "Memento_Sailor_1_3":
			dialog.text = "悪いな、それについては話さないほうがいい。";
			link.l1 = "「なぜそのまま立ち去らないんだ？」";
			link.l1.go = "Memento_Sailor_1_4";
		break;

		case "Memento_Sailor_1_4":
			dialog.text = "どこへ行く？少なくともここならまだ望みがある。運が味方してくれるかもしれねえ。どの船にもそれぞれの運命がある。 グリムにはグリムの、お前にはお前の運命がな。俺たちは人間じゃねえ、ただの航海日誌の数字さ。";
			link.l1 = "俺の船じゃ、事情が違うんだ。";
			link.l1.go = "Memento_Sailor_1_5";
		break;
		
		case "Memento_Sailor_1_5":
			dialog.text = "おっしゃる通りです、船長。ごきげんよう。";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_2":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "この立派な船に客人が来るのは久しぶりだな！";
				link.l1 = "お前は水夫か？そうは見えねえな。";
				link.l1.go = "Memento_Sailor_2_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "他に何かありますか、船長？";
				link.l1 = "「何もない。」";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_2_1":
			dialog.text = "はっ！船長が俺を牢屋からそのまま買い取ったんだ。ポートロイヤルで絞首刑になるはずだった――詩ばかり朗読してたキザ野郎を刺しちまってな。あんな奴、当然の報いだぜ。";
			link.l1 = "じゃあ、運が良かったってわけか？";
			link.l1.go = "Memento_Sailor_2_2";
		break;

		case "Memento_Sailor_2_2":
			dialog.text = "もちろんだぜ！船長はケチじゃねえが、時々あいつの……遊びに付き合わなきゃならねえんだよ。";
			link.l1 = "どんな遊びだ？";
			link.l1.go = "Memento_Sailor_2_3";
		break;
		
		case "Memento_Sailor_2_3":
			dialog.text = "毎週くじ引きをやるんだ：短い棒を引いたら危険な仕事、時には海に飛び込むこともある。本当に笑っちまうぜ。 誰にでもできることじゃねえが、船長はこうやって価値のねえ奴をふるい落とすって言ってるんだ。";
			link.l1 = "何に値しないって？";
			link.l1.go = "Memento_Sailor_2_4";
		break;

		case "Memento_Sailor_2_4":
			dialog.text = "知るかよ？船長は話すのが大好きで、まるで神父みてえに説教するんだ。「死と向き合ってこそ、 本当に生きることができる！」ってな。\n"+
			"（彼は唾を吐く。）";
			link.l1 = "甲板に唾を吐いたら鞭打ちだぜ。お前は水夫じゃなくてただの無法者みてえな振る舞いだ。じゃあな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_3":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "ごきげんよう、船長。";
				link.l1 = "どうしてここに来たんだ？";
				link.l1.go = "Memento_Sailor_3_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "他に何かあるか、船長？";
				link.l1 = "「何もない。」";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_3";
		break;

		case "Memento_Sailor_3_1":
			dialog.text = "グリム船長が俺の乗っていた奴隷船を奪ったんだ。俺は船倉で病気になって、死にかけていた……あまり覚えていない。\n気がついたら、ここ「メメント」にいたんだ。";
			link.l1 = "「それで、他の奴隷たちはどうなったんだ？」";
			link.l1.go = "Memento_Sailor_3_2";
		break;
		
		case "Memento_Sailor_3_2":
			dialog.text = "わからねえ。船長は全員を解放したって言ってたが、乗船させられたのは俺だけだった。他の連中は島々に散ったか、 傷がもとで死んじまったんだろう。その日のことは、俺にはぼんやりとしか覚えてねえんだ。";
			link.l1 = "少なくとも今は自由だな。";
			link.l1.go = "Memento_Sailor_3_3";
		break;

		case "Memento_Sailor_3_3":
			dialog.text = "自由だと？ここに自由な奴なんていねえよ。船長は金も食い物も服もくれるが、その代わりに絶対の忠誠を要求する――それに、あの忌々しいくじまで引かせやがるんだ。";
			link.l1 = "くじか？";
			link.l1.go = "Memento_Sailor_3_4";
		break;

		case "Memento_Sailor_3_4":
			dialog.text = "毎週、誰かがくじで短い棒を引いて危険な仕事を任される――全員が戻ってくるわけじゃねえ。船長は「それが生きてる奴と死んだ奴を分ける方法だ」と言ってるぜ。";
			link.l1 = "「それを我慢してたのか？」";
			link.l1.go = "Memento_Sailor_3_5";
		break;

		case "Memento_Sailor_3_5":
			dialog.text = "誰もが運が味方してくれることを願っている。船長は皆を突き動かすものを知っている――絞首刑への恐怖、金への欲、命を救われた恩を返したいという衝動。だが、そんなものは俺には関係ねえ。 金なんざ要らねえし、覚えてもいねえことにどうして借りができるってんだ？";
			link.l1 = "そんなにあけすけに話して、怖くねえのか？";
			link.l1.go = "Memento_Sailor_3_6";
		break;

		case "Memento_Sailor_3_6":
			dialog.text = "俺に何ができるってんだ？ここは死者の船だぜ、船長。俺はここに属してる。だが、お前は――お前は違う。";
			link.l1 = "そうかい。じゃあな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_3";
		break;
		
		case "Memento_Sailor_4":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "「メメント号へようこそ、船長。」";
				link.l1 = "海賊船にスペイン兵がいるなんて、そうそう見られるもんじゃねえな。";
				link.l1.go = "Memento_Sailor_4_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "他に何かあるか、船長？";
				link.l1 = "「何でもない。」";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_4";
		break;

		case "Memento_Sailor_4_1":
			dialog.text = "俺は脱走兵だ。グリム船長がサンホセ広場の絞首台から俺を買い取ったんだぜ。高い代償だった――俺みたいなクズのためにドゥブロン金貨一袋も払いやがった。";
			link.l1 = "「何の罪で吊されたんだ？」";
			link.l1.go = "Memento_Sailor_4_2";
		break;

		case "Memento_Sailor_4_2":
			dialog.text = "サルド副官に命じられて、俺たちはジャングルで労働者の護衛をしてたんだ。あそこじゃ一週間で半分が熱病で死ぬ。 俺の命はもっと価値があると思ったのさ。今は、その命に値札をつけた男に仕えてるってわけだ。";
			link.l1 = "後悔はないのか？";
			link.l1.go = "Memento_Sailor_4_3";
		break;

		case "Memento_Sailor_4_3":
			dialog.text = "縄は長くねじれるもんさ……船長は忠実な者には気前がいい。\nだが時には変な試練を与える――くじ引きだ。\n運に恵まれない奴もいるんだぜ。";
			link.l1 = "くじ引きか？";
			link.l1.go = "Memento_Sailor_4_4";
		break;
		
		case "Memento_Sailor_4_4":
			dialog.text = "知ってるだろう。嵐の中でマストに登らされる奴もいれば、先陣に立たされる奴もいる。船長は、 それでお前が覚悟できてるか試すんだとさ。何の覚悟かはわからねえが、運が味方してくれるといいんだがな。";
			link.l1 = "…幸運を祈るぜ…まあな。";
			link.l1.go = "Memento_Sailor_4_5";
		break;

		case "Memento_Sailor_4_5":
			dialog.text = "ありがとうございます、船長。死は遅かれ早かれ誰にも訪れるものです。";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
		/*case "Memento_Sailor_5":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "「ダイアログ5」";
				link.l1 = "「ダイアログ5」";
				link.l1.go = "exit";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "他に何かあるかい、船長？";
				link.l1 = "「何でもない。」";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_5";
		break;*/
		
		case "Memento_MortimerGrim_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "ようこそメメント号へ、相棒。俺の名はモーティマー・グリムだ。";
				link.l1 = "Captain "+GetFullName(pchar)+"……お招きいただき、ありがとうございます……";
				link.l1.go = "Memento_MortimerGrim_2";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "他に何を話そうか？";
				if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
				{
					link.l1 = "素晴らしい剣だな、船長。";
					link.l1.go = "Memento_MortimerGrim_question_1_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
				{
					link.l2 = "骸骨の隣にあるお前の望遠鏡、なかなか様になってるぜ。";
					link.l2.go = "Memento_MortimerGrim_question_2_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
				{
					link.l3 = "正直に言うと、お前の船員たちはずいぶんと寄せ集めの連中だな。";
					link.l3.go = "Memento_MortimerGrim_question_3_1";
				}
				link.l4 = "……何もないさ、同僚。順風を祈るぜ。";
				link.l4.go = "exit";
				NextDiag.TempNode = "Memento_MortimerGrim_1";
			}
		break;

		case "Memento_MortimerGrim_2":
			dialog.text = "カリブ海は絞首台に急ぐ者には寛大だ、それだけは俺も知ってるぜ。";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_3";
		break;
		
		case "Memento_MortimerGrim_3":
			dialog.text = "はい？何か聞きたいことでもあったのか？";
			link.l1 = "お前の後ろに骸骨がぶら下がってるぜ。";
			link.l1.go = "Memento_MortimerGrim_4";
			link.l2 = "今日はいい風だな、そうだろ？天気も最高だぜ。";
			link.l2.go = "Memento_MortimerGrim_5";
		break;

		case "Memento_MortimerGrim_4":
			dialog.text = "「骸骨だと？俺の後ろにあるのは青いカリブ海だけだぜ。」";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_5":
			dialog.text = "同感だぜ、相棒。毎日こんな日だったら最高だな！";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_6":
			dialog.text = "ハハハ！その冗談は何度聞いても飽きねえな！驚くなよ――ヨリックの頭蓋骨も、この船と同じく、俺の昔の人生の形見なんだ。文字通りにな、保証するぜ。";
			link.l1 = "「文字通り？」";
			link.l1.go = "Memento_MortimerGrim_7";
		break;

		case "Memento_MortimerGrim_7":
			dialog.text = "同僚よ、死を恐れるか？脅してるわけじゃねえ、本当に興味があるんだ。";
			link.l1 = "もちろんだ。他に言う奴は嘘つきだぜ。";
			link.l1.go = "Memento_MortimerGrim_8_leadership";
			link.l2 = "いいや。俺たち全員、結局あそこに行くことになるんだ。";
			link.l2.go = "Memento_MortimerGrim_8_weapon";
			link.l3 = "お前は？";
			link.l3.go = "Memento_MortimerGrim_8_sneak";
		break;
		
		case "Memento_MortimerGrim_8_leadership":
			dialog.text = "おお！死こそがすべての恐怖の母だ。孤独も、闇も、罰も――それらはすべて彼女の仮面にすぎない。";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Memento_MortimerGrim_8_weapon":
			dialog.text = "おお！死はすべての恐怖の母だ。孤独も、闇も、罰も――それらはみな死の仮面にすぎねえ。";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "Memento_MortimerGrim_8_sneak":
			dialog.text = "おお！死はすべての恐怖の母だ。孤独も、闇も、罰も――それらはみな死の仮面にすぎねえ。";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Memento_MortimerGrim_9":
			dialog.text = "遠くを見る必要はねえ。ヨリック爺さんを見てみろよ――肋骨にランタンをぶら下げた骨の山さ。それでも、あんたみたいな怖い船長ですらビビっちまったじゃねえか！";
			if (startHeroType == 4)
			{
				dialog.text = "遠くを見る必要はねえ。ほら、ヨリック爺さんを見てみろよ。肋骨にランタンを突っ込んだ骨の山だ――あの大物ショーン・マッカーサーの娘、怖いもの知らずのエレンでさえビビったんだぜ！\n";
			}
			link.l1 = "口は達者だが、それをどうするつもりかはまだ言ってないぜ。";
			link.l1.go = "Memento_MortimerGrim_10";
		break;

		case "Memento_MortimerGrim_10":
			dialog.text = "何をすればいいかは分かってるが、俺の治療法が誰にでも合うわけじゃねえ。\n試してみるのは自由だが、まずはお前の考えを聞かせてくれ。";
			link.l1 = "聖書には死は存在しないと書かれている。";
			link.l1.go = "Memento_MortimerGrim_11_1";
			link.l2 = "俺が怖気づいたら、この船は終わりだ。";
			link.l2.go = "Memento_MortimerGrim_11_2";
			link.l3 = "答えはラム酒の瓶の底に沈んじまった。";
			link.l3.go = "Memento_MortimerGrim_11_3";
		break;
		
		case "Memento_MortimerGrim_11_1":
			dialog.text = "それは確かだ。その本で俺が同意できるのはそれだけだ。";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_2":
			dialog.text = "見事だ。しかし心配することはない。死など存在しないのだ。";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_3":
			dialog.text = "ヨーホーホー！皮肉屋だな。でもラムがなくても言うぜ：死なんてねえんだ。";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_12":
			dialog.text = "簡単なことさ。本当の人生は死を乗り越えて初めて始まるんだ。俺はその向こう側――あの帳の向こうに行ったことがある。信じてくれ、それからこそ、本当に生き始めたんだぜ。";
			link.l1 = "「もう一度言ってくれ？」";
			link.l1.go = "Memento_MortimerGrim_13";
		break;

		case "Memento_MortimerGrim_13":
			dialog.text = "気にするな、相棒。";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
		break;

		case "Memento_MortimerGrim_question_1_1":
			dialog.text = "気づいてくれて嬉しいぜ、相棒！俺は自慢するつもりはねえが、恐ろしいカットラスも持たねえで海賊なんて言えるか？";
			link.l1 = "「それが本当に重要なのか？」";
			link.l1.go = "Memento_MortimerGrim_question_1_2";
		break;
		
		case "Memento_MortimerGrim_question_1_2":
			dialog.text = "その通りだ！俺が私的な理由で船の財宝を大きく減らした唯一の時は、まさにこの剣のためだったんだ。 二千枚の金ドゥブロンだぜ、相棒！くそっ、もしもう一度墓場から這い上がれるなら、 この剣の値段のためだけに戻ってくるさ！\n"+
			"武器自体は素晴らしい。だが、どうも……何かが足りない気がするんだ。";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "Memento_MortimerGrim_question_2_1":
			dialog.text = "誰かからの贈り物だ。他の誰よりも死を理解し、しかも話が抜群に面白い——見ての通り、想像力もとんでもなく豊かなんだ。";
			link.l1 = "厳しい状況だな。";
			link.l1.go = "Memento_MortimerGrim_question_2_2";
		break;

		case "Memento_MortimerGrim_question_2_2":
			dialog.text = "メメント・モリだぜ、相棒。";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_2 = true;
		break;

		case "Memento_MortimerGrim_question_3_1":
			dialog.text = "俺の船員たちは、お前の連中よりも互いに共通点が多いぜ、例えばな…全員、俺が縄や鎖から解放してやった奴らだ。誰もが死の息吹を感じたことがある。そういうものは、 血や旗よりも人を強く結びつけるんだ。";
			link.l1 = "じゃあ、酒場で人を雇ったりはしねえんだろうな？";
			link.l1.go = "Memento_MortimerGrim_question_3_2";
		break;

		case "Memento_MortimerGrim_question_3_2":
			dialog.text = "奴隷船の船倉や絞首台をメメント号の甲板と交換できるとなりゃ、 元奴隷や死刑囚どもが喜んで仲間になるのに驚くだろうな。今じゃ俺の船員は178人――そいつら全員が俺に借りがあるってわけだ。";
			link.l1 = "だが、それでも奴らに給料を払って船を維持しなきゃならねえ。感謝の気持ちだけじゃやっていけねえんだ。";
			link.l1.go = "Memento_MortimerGrim_question_3_3";
		break;

		case "Memento_MortimerGrim_question_3_3":
			dialog.text = "俺は成功した海賊だぜ、相棒。まさに「人類の敵」ってやつさ。本当の人類の敵――奴隷商人や王冠をかぶった連中――は、俺のことをそう呼ぶだろう。やつらとの違いは、肩書きだけさ。\n"+
			"幸いなことに、あいつらは金貨をたっぷり持ってやがる。俺は奴隷商人の宝箱から出てきたコインを使って、 王冠に死刑を宣告された奴らを救ってるんだ。残りは全部、俺の仲間にやる――俺には何もいらねえ。死んだ人間に金なんて何の役にも立たねえだろ？そのうち、あいつらも気づくだろうさ……";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_3 = true;
		break;
		
		// Диалог с Алонсо
		case "Memento_Alonso_phantom_11":
			dialog.text = "「これが俺たちのクソみてえな状況だぜ、船長。」";
			link.l1 = "これは何だ！？";
			link.l1.go = "Memento_Alonso_phantom_12";
		break;

		case "Memento_Alonso_phantom_12":
			dialog.text = "お前だけが残ったんだ。病が俺たち全員をやっちまった。お前には失望したぜ。";
			link.l1 = "そんなはずない！";
			link.l1.go = "Memento_Alonso_phantom_13";
		break;

		case "Memento_Alonso_phantom_13":
			dialog.text = "呪われた船に俺たちを乗せやがったな。";
			link.l1 = "...";
			link.l1.go = "Memento_Alonso_phantom_14";
		break;

		case "Memento_Alonso_phantom_14":
			dialog.text = "「お前が俺たち全員を破滅させたんだ！」";
			link.l1 = "アロンソ、どうしたんだ！？";
			link.l1.go = "Memento_Alonso_phantom_15";
			npchar.model = "skel1";
			npchar.model.animation = "skeleton";
			npchar.sex = "skeleton";
			Characters_RefreshModel(npchar);
			SetMusic("classic_music_retribution_1");
		break;

		case "Memento_Alonso_phantom_15":
			dialog.text = "「死者は生者に教える。」";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_6");
		break;
		
		// Диалог с Гримом
		
		case "Memento_MortimerGrim_phantom_11":
			dialog.text = "どうして止まったんだ、相棒？気が変わったのか？じゃあ最初からなんで襲いかかってきたんだ？";
			link.l1 = "陰気だと？でもお前は死んでるじゃねえか！";
			link.l1.go = "Memento_MortimerGrim_phantom_12";
		break;

		case "Memento_MortimerGrim_phantom_12":
			dialog.text = "はっ！死んだものは決して死なねえんだぜ。それに、話を急ぎすぎじゃねえか？白兵戦には勝ったかもしれねえが……生き残れるかどうかは――さあ、見せてもらおうじゃねえか！";
			link.l1 = "その戦いは何週間も前に終わったんだ！お前はもう死んでるはずだ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_11");
		break;

		case "Memento_MortimerGrim_phantom_21":
			dialog.text = "これで終わったな。勝利おめでとう。";
			link.l1 = "「陰気か？」";
			link.l1.go = "Memento_MortimerGrim_phantom_22";
			LAi_UseAtidoteBottle(pchar);
		break;

		case "Memento_MortimerGrim_phantom_22":
			dialog.text = "なあ、俺は嬉しいんだ。本当に、お前が俺を殺してくれて心から嬉しい。マジでな。";
			link.l1 = "何の話だ？";
			link.l1.go = "Memento_MortimerGrim_phantom_23";
		break;

		case "Memento_MortimerGrim_phantom_23":
			dialog.text = "俺は臆病者だぜ、相棒。死を恐れた哀れな臆病者さ――何千人もそうだったようにな。\n乗組員が疫病で死んだ時……しかもそれが俺のせいだった時、恐怖で気が狂っちまった。\n死者の船で一人、ひと月も漂流したんだ。";
			link.l1 = "「本当は何が起きたんだ？」";
			link.l1.go = "Memento_MortimerGrim_phantom_24";
		break;

		case "Memento_MortimerGrim_phantom_24":
			dialog.text = "俺は死の試練に失敗した。\nそれを受け入れて生き延び、何かを学ぶ代わりに、ますます恐怖に囚われたんだ。\nそしてその恐怖を紛らわせるために……俺は他人にも自分と同じ苦しみを味あわせるようになった。";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_25";
		break;
		
		case "Memento_MortimerGrim_phantom_25":
			dialog.text = "ありがとう、同志よ。こんな……存在から俺を解放してくれて。今こそ本当に死は存在しないと知った。もう恐れはない。責める相手も、縛る相手も、 誰も残っていない。";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_26";
		break;

		case "Memento_MortimerGrim_phantom_26":
			dialog.text = "メメントを船長から引き離すな。モーティマー……モーティマー船長はいい男だった。ドミニカで彼を探せ。そして船……その船がお前を受け入れてくれるだろう。";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_27";
		break;

		case "Memento_MortimerGrim_phantom_27":
			dialog.text = "「Mortui vivos docent」だ、同僚よ。死者は生者に教える。さらばだ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_13");
		break;
		
	}
} 