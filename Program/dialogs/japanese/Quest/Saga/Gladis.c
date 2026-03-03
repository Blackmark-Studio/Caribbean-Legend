// Глэдис МакАртур - приемная мать Элен
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if(pchar.questTemp.Saga == "helena1")
			{
				dialog.text = "ああ、船長！実はな、俺はヘレンに全部話したんだ。どれほど心が軽くなったか、想像もできねえだろう！";
				link.l1 = "すべて正しくやってくれましたわ、マクアーサー嬢。\nあの娘には真実を知る必要がありますの。そして私は彼女のためにここにいるのですわ。";
				link.l1.go = "Helena_hire";
			}
			else
			{
				dialog.text = "「ごきげんよう。」 "+pchar.name+"！会えて嬉しいぜ！ラムでも飲むか？";
				link.l1 = "ありがとうございます、マッカーサー嬢。でも、今はあまりにも忙しいのです。";
				link.l1.go = "exit";			
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "FindHelena":
			dialog.text = "何の用だ、旦那？";
			link.l1 = "あなたがグラディス・マッカーサーか？";
			link.l1.go = "FindHelena_1";
		break;
		
		case "FindHelena_1":
			dialog.text = "そうだ。お前のことは覚えていないな、若造。\nそれで、俺に何の用か説明してくれないか？";
			link.l1 = "マッカーサー嬢、あなたの娘さんの失踪について興味があります。何が彼女が消えたと思わせたのですか？ ヘレンにはとても腕の立つ乗組員がいたと聞いていますが…";
			link.l1.go = "FindHelena_2";
		break;
		
		case "FindHelena_2":
			dialog.text = "ああ、間違いありません！見てください、亡き夫の命日は五日前でした。エレンは父親をとても愛していて、 この日を絶対に忘れたりしません。彼女は親しいミスキート族からレッドウッドの荷を受け取るため、 数日だけ出かけていただけです。\nインディアンたちは私たちの後ろ盾であるヤン・スヴェンソンを敬い、恐れていますから、 彼女に危害を加えることは絶対にありません。スヴェンソン旦那もすでに彼らと話をつけています。 木材はその日のうちに積み込まれました。それ以来、誰もエレンを見ていません。";
			link.l1 = "もしかして海賊たちが彼女を襲ったのか？";
			link.l1.go = "FindHelena_3";
		break;
		
		case "FindHelena_3":
			dialog.text = "馬鹿なことを言うな！スヴェンソン旦那が五人の海賊男爵の一人であり、 カリブ海兄弟評議会のメンバーだってことはもう知っているはずだろう。 彼の許可なしにここで海賊が狩りをすることは許されていないんだ。ただし、もしかしたら新参者かもしれないがな…";
			link.l1 = "それで、スペイン人はどうなんだ？彼女がスペインの哨戒隊に遭遇した可能性はあるのか？";
			link.l1.go = "FindHelena_4";
		break;
		
		case "FindHelena_4":
			dialog.text = "私は政治には疎いが、ここの金銀鉱山はすっかり掘り尽くされてしまい、 貴族のイダルゴたちが命を賭けてまで狙うような財宝ももうほとんど残っていないそうだ。 だから彼らはここでは珍しい客人なんだよ。それに、インディオたちは彼らに敵対的だしな。\nスペインの巡回隊と偶然出くわしたとしても、ヘレンにとって悪い結果にはならなかったはずだ。彼らの視点から見れば、 ヘレンは何も違法なことはしていない。「レインボー」はオランダの旗を掲げていたし、 ヘレンの書類もすべて揃っていた。交易許可証も含めてな。";
			link.l1 = "彼女が最近の航海に出る前に、何か変わったことは起きなかったか？もしかして、見落としていた不思議な出来事とかは？ ";
			link.l1.go = "FindHelena_5";
		break;
		
		case "FindHelena_5":
			dialog.text = "ああ、違うよ！ありがたいことに、ここでは平和に暮らしているんだ。ただ、 数週間前にヘレンがまたしても望まぬ求婚者からデートをせがむ手紙を受け取ったんだ。あの子は可愛いけど、 お金持ちじゃないからね。\nだから言い寄る男はたくさんいるけど、誰のことも好きじゃないし、結婚もしたくないんだ。 そうやって今まで何人も手玉に取ってきたよ。本当に軽薄で、まるで母親そっくりさ！";
			link.l1 = "あなたはそんなタイプの女性には見えませんね、マクアーサー嬢……";
			link.l1.go = "FindHelena_6";
		break;
		
		case "FindHelena_6":
			dialog.text = "何だって？ああ、もうどうでもいい、俺は失恋中なんだ。何の話をしてたっけ？ああ、そうだ、手紙のことだ。とにかく、 その手紙はジミー・ヒギンズが書いたんだ。あいつはジャックマンの手下で、マルーンタウンに住んでる。 うちの町にもよく来るぜ。ジャックマンも海賊男爵の一人だけど、 スヴェンソン旦那はあいつのことが気に入らねえみたいだ、理由は知らねえけどな。";
			link.l1 = "「それで、エレンは？」";
			link.l1.go = "FindHelena_7";
		break;
		
		case "FindHelena_7":
			dialog.text = "ああ、彼女は声を上げて笑っていたよ。前の日にはイギリスのコルベット艦長から求婚されて、それすら断ったんだ。 なのに今度は海賊のオンボロ船のただのボースンかよ……ありえねえ、ショーン・マッカーサーの娘はもっと堂々とした旦那を求めてるんだ！";
			link.l1 = "それで、そのイギリス人船長の名前は何だったんだ？";
			link.l1.go = "FindHelena_8";
		break;
		
		case "FindHelena_8":
			dialog.text = "ああ、俺が知るわけないだろ？本物の紳士なんてここじゃ珍しい客さ。悪かったな、 別に気を悪くさせるつもりはなかったんだ。あのヒギンズに聞いてみな。あいつなら名前を覚えてるはずだ。 ジミーはヘレンを巡ってあの船長と決闘しようとしてたんだよ。仲間たちがなんとか止めたけどな。でも、 二人ともヘレンが出航する数日前にブルーヴェルドを離れちまったよ。";
			link.l1 = "さて、お話を聞かせてくれてありがとう。あなたの大切な人を探してみます。何か分かったら、 あなたかスヴェンソン旦那に伝えます。娘さんが無事で生きて見つかることを願っています。";
			link.l1.go = "FindHelena_9";
		break;
		
		case "FindHelena_9":
			dialog.text = "彼女を探しに行くのですか？神があなたと共にあり、あなたを導き、その手を強めてくださいますように！ 私はあなたのために祈ります！\nお名前を教えていただけますか、立派なお方？";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+"。すぐに良い知らせを持って戻れることを願っています、マッカーサー嬢。ごきげんよう！";
			link.l1.go = "FindHelena_10";
		break;
		
		case "FindHelena_10":
			DialogExit();
			NextDiag.CurrentNode = "FindHelena_wait";
			AddQuestRecord("Saga", "1");
			pchar.questTemp.Saga = "maruntown";//идем к Джекману
			SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
			int iTime = 25-MOD_SKILL_ENEMY_RATE;
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime*2, false);
			}
			else SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;
		
		case "FindHelena_wait":
			dialog.text = "「私の可哀想な娘について何か新しい情報はありますか、」 "+pchar.name+"?";
			link.l1 = "申し訳ありません、マッカーサー嬢、今のところ新しい報告はありませんが、どうか落ち込まないでください。 私は引き続き捜索を続けます。悪い知らせがないということ自体が良い知らせですわ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "FindHelena_wait";
		break;
		
		case "Helena_die":
			dialog.text = "遅かったのだ、船長。私の可哀想な娘の遺体がアンティグアの岸辺で見つかった。神よ、 あの子が死ぬ前にどれほど酷く拷問されたことか！私は美しい娘を守れなかった……";
			link.l1 = "申し訳ありません。私にはどうすることもできませんでした……";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_exit":
			dialog.text = "ああ、若者よ、頼む、私をこの悲しみにひとりにしてくれ……";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_regard":
			dialog.text = "娘を救ってくださったこと、船長、どう感謝してよいかわかりません。\n娘からすべて聞きましたし、あなたの勇気と名誉に心から敬服しております。\nどうぞ、この金のドブロンをお受け取りください。多くはありませんが、心からの贈り物です。\nそして、絶対に断るなどとは考えないでください！";
			link.l1 = "わかったよ、グラディス、もう言わないさ。だが、俺は金のためにあんたの娘を助けたんじゃねえってこと、 わかっててほしいんだ。";
			link.l1.go = "Gladis_regard_1";
			link.l2 = "この金は自分のために取っておきな、グラディス。俺よりお前の方が必要だろう。";
			link.l2.go = "Gladis_regard_2";
			sld = characterFromId("Helena");
			LAi_SetStayType(sld);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			// открыть город
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;
		
		case "Gladis_regard_1":
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "あなたの立派な行いに、少しでも報いることができて嬉しいです。\n私の家の扉はいつでもあなたのために開かれています。\nエレンも私も、いつでもあなたにお会いできるのを楽しみにしています。";
			link.l1 = "ありがとうございます、マッカーサー嬢。機会があれば、あなたとエレンを訪ねます。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_regard_2":
			dialog.text = "ああ、どうか……私はただ、あなたの立派な行いに報いたかっただけです。私の家の扉はいつでもあなたのために開かれています。\nエレンも私も、いつでもあなたにお会いできるのを楽しみにしています。";
			link.l1 = "ありがとうございます、マクアーサー嬢。機会があれば、あなたとエレンにお伺いします。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
			pchar.questTemp.Saga.Helena_friend = "true";//атрибут поведения Элен в будущем
		break;
		
		case "Gladis_wait":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys")) {
				dialog.text = "船長、あなたはいつでも我が家に大歓迎です！ヘレンに会いに来たのですか？残念ですが、 彼女は自分の部屋に閉じこもっています――ここ数日で相当疲れてしまったのでしょう。心配しないでください、彼女には時々こういうことがあるんです。";
				link.l1 = "本当か？彼女は本当に無事なんだな？";
				link.l1.go = "after_drinking";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys");
				break;
			}
		
			dialog.text = "ああ、ド・モール様！娘の命の恩人であるあなたを我が家でお迎えできて、いつも嬉しく思います。\nエレンに会いたいのですか？彼女は二階の自室におります。\n「レインボー」号を失い、あの劇的な救出劇の後、彼女は外出を避けております。\nあんなに取り乱した様子のエレンを見るのは、私も初めてです……";
			link.l1 = "ありがとうございます、マッカーサー嬢。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_history":
			dialog.text = "ああ、ド・モール様！私の娘の命の恩人であるあなたを、いつも我が家でお迎えできて嬉しいです。 エレンにお会いになりたいのですか？";
			link.l1 = "いいや。君にいくつか質問したいんだ、そして率直に答えてほしい。\nエレンの安全がかかっているんだ。この指輪に見覚えはあるか？";
			link.l1.go = "Gladis_history_1";
		break;
		
		case "Gladis_history_1":
			RemoveItems(pchar, "bucher_ring", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "なんてことだ！これは…彼女の父親の指輪だ！";
			link.l1 = "マッカーサー旦那のか？";
			link.l1.go = "Gladis_history_2";
		break;
		
		case "Gladis_history_2":
			dialog.text = "いいや。エレンは俺たちの義理の娘だが、本人はそれを知らねえ。両親が亡くなったから、 俺が自分の子として引き取ったんだ。ショーンも彼女を養子にしたが、 あいつもエレンが俺の実の娘じゃねえことは知らなかったんだ。";
			link.l1 = "「じゃあ、彼女の本当の親は誰なんだ？」";
			link.l1.go = "Gladis_history_3";
		break;
		
		case "Gladis_history_3":
			dialog.text = "彼女の父親は「ブッチャー」と呼ばれた海賊で、フリゲート艦「ネプチューン」に乗っていたのは知っている。 俺が彼を見たのは二度だけだ。母親は若くて美しい女で、赤毛で男物の服を着ていた。 それが彼女について俺が話せるほとんど全てだ――あとは、母親がひどい母親だったってことくらいだ。\n俺ならあんな赤ん坊を他人の手に預けたりはしなかった。二人とも悲劇的な最期を遂げた。 そして約束された使者が二十年後に現れたと思ったら、それがあんただった。ブッチャーがあんたを寄越したのか？ あいつはまだ生きてるのか？";
			link.l1 = "落ち着いてください、グラディス嬢！肉屋が戻ってきたと疑う理由はありませんよ。ただ、 あなたがその考えを持った二人目の方です。最近、あなたにこの指輪を見せるはずだった男に会いました……";
			link.l1.go = "Gladis_history_4";
		break;
		
		case "Gladis_history_4":
			dialog.text = "...";
			link.l1 = "ちょっとした出来事のせいで彼は間に合わず、船長の最後の命令を果たせなかったことを一生悔やみ続けたんだ。 彼はつい最近亡くなって……まあ、悲しい話はこのくらいにしよう。\nグラディス、ヘレンの母親は娘のために何か形見を残していったのかい？小さな物でもいい、何かあったか？";
			link.l1.go = "Gladis_history_5";
		break;
		
		case "Gladis_history_5":
			dialog.text = "彼女は古い地図の奇妙な一片を私に残したんだ。自分の遺産だと冗談めかして言っていたよ。 あんな紙切れが何の役に立つっていうんだ？私はただの悪い冗談だと思っていた。彼女は興奮しすぎて、 少し正気じゃなかった。でも、この「贈り物」は取っておいたんだ。\nどうなるかわからないしな……もし君が望むなら、いつか全部話してくれると約束してくれるなら、これを君にあげてもいいぞ。";
			link.l1 = "もちろんです、マクアーサー嬢。しばらくこのくず野郎を預かります。スヴェンソン旦那と話が必要です。";
			link.l1.go = "Gladis_history_6";
		break;
		
		case "Gladis_history_6":
			GiveItem2Character(pchar, "map_half_beatriss"); //половинка карты
			PlaySound("interface\important_item.wav");
			dialog.text = "またしても助けていただきましたわ、ド・モール様！どう感謝すればよいのか分かりません。どうか、 せめて夫のピストルをお受け取りくださいませ。夫はいつもこの銃を自慢しておりましたし、 とても珍しいものだと言っておりました。長い間ここに置きっぱなしでしたの。あなたのお役に立ててくださいまし！ どうぞ、お受け取りください、お願いですわ！";
			link.l1 = "ありがとう、グラディス。このピストルは本当に素晴らしい。ありがとう、そしてさようなら。";
			link.l1.go = "Gladis_history_7";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l2 = "このピストルはエレンに持たせてやれ。俺には武器は十分ある。";
				link.l2.go = "Gladis_history_8_1";
			}
		break;
		
		case "Gladis_history_7":
			DialogExit();
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol5");
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			AddQuestRecord("Saga", "22");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		
		case "Gladis_history_8_1":
			dialog.text = "でも、どうして私の贈り物を受け取ってくれないのですか？悲しくなってしまいますわ…";
			link.l1 = "今ならあなたを幸せにできると思います。これから、 ブッチャー船長の娘の安全を守るために使者があなたに届けるはずだった金貨をお返しします。\nもちろん、このドゥブロン金貨だけであなたの愛や忠誠心すべてに報いることはできませんが、 これは正当にあなたのものです。どう使うかはあなたの自由です。";
			link.l1.go = "Gladis_history_8";
		break;
		
		case "Gladis_history_8":
			dialog.text = "ああ、船長！何と言えばいいのかわかりません……こんなにも……高潔な方がこの世にいるとは思いもしませんでした！娘のところへ行って、この良い知らせを伝えてください！";
			link.l1 = "ただいま向かっています、マクアーサー嬢。";
			link.l1.go = "Gladis_history_9";
		break;
		
		case "Gladis_history_9":
			DialogExit();
			RemoveItems(pchar, "chest", 1);
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Saga", "22");
			sld = characterFromId("Helena");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterbyItem(sld, "pistol5");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
		break;
		
		case "Helena_hire":
			dialog.text = "本気か？どういう意味だ？";
			link.l1 = "スヴェンソン旦那の依頼により、私はヘレンを自分の船の士官として雇うつもりです。\n彼女は非常に危険な状況にあります。\nヤンと私がこの件に取り組んでいる間、ヘレンには確かな護衛が必要です。\n私がその護衛を提供できることを願っています。";
			link.l1.go = "Helena_hire_1";
		break;
		
		case "Helena_hire_1":
			dialog.text = "ああ、これは本当にありがたい！自分からこんなこと頼む勇気はなかったよ。これであの子を守るには最高の手段だ。 ヘレンもまた航海できるって大喜びするだろう！";
			link.l1 = "お褒めいただきありがとうございます、マッカーサー嬢。さて、今度はあなたの……義娘に会わねばなりません。";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_hire";
			pchar.questTemp.Saga = "helena2";
		break;
		
		case "saw_sex":
			dialog.text = "「ああ、神よ！私の可愛い娘よ！」";
			link.l1 = "グラディス、ノックの仕方も知らないのか！？";
			link.l1.go = "saw_sex_1";
		break;
		
		case "saw_sex_1":
			dialog.text = "おお、許してくれ、若者たちよ！私はもう行くぞ！ヘレン、私が言ったことを忘れるなよ！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysTalk");
		break;
		
		case "after_drinking":
			dialog.text = "今回は彼女がただ働きすぎただけだと思います。全部話してくれましたよ、船長！ 昨日は彼女が新しい船を選ぶのを手伝ってくださって、ありがとうございました！";
			link.l1 = "ん？うん、どういたしまして。さようなら、マッカーサー夫人。";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
