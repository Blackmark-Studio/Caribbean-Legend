// Алонсо де Мальдонадо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何かご用ですか？";
			link.l1 = "「いや、何もない。」";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "ksochitam":
			dialog.text = "止まれ、船長 "+GetFullName(pchar)+"...";
			link.l1 = "どういうわけか、ここにスペイン兵がいるのももう驚かなくなったな……誰かにずっと追われるのには慣れっこさ。\nこんな神に見捨てられた島で何を探してるんだ、カスティーリャ野郎？楽にくたばれる方法でも探してるのか？";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "私の名はアロンソ・デ・マルドナードだ。\nお前には何の意味もないかもしれねえが、ディエゴ・デ・モントヤの名なら聞き覚えがあるだろう。\nあいつは俺の親友だった。命の恩人でもある。だが今や、あいつの血はお前の手に付いているんだ。";
			link.l1 = "俺を追ってここまで来たのは、復讐が目的か？";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "俺が求めているのは復讐だけじゃねえ。俺の理解では、お前がククルカンの仮面を持ってるんだろう？";
			link.l1 = "なんてこった！また宝探しかよ！ドン・ディエゴが始めた未完の仕事を片付けに来たのか？";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			dialog.text = "俺は宝なんかに興味はねえ。タイアサルの財宝は見たことがある。 ミゲル・ディチョソもほんの一欠片しか持ち出せなかった。俺が欲しいのは仮面だ。";
			link.l1 = "お前、タヤサルに行ったのか？それは信じがたいな。俺の記憶では、遠征の唯一の生存者はディチョソだけだったはずだ。 ";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			dialog.text = "俺はディチョソが来る二十年前にテヤサルへ行ったんだ。あの狂った呪術師カネクが、 この島に仮面を隠すために忌まわしい人身御供の儀式を使ったのも、その時だった。";
			link.l1 = "信じられない話だ！お前は「真実の守護者」が生まれた時に生け贄として連れてこられた征服者どもの一味だったのか？ お前たちは皆、死んだはずだ！";
			link.l1.go = "ksochitam_5";
		break;
		
		case "ksochitam_5":
			dialog.text = "俺たち全員じゃねえ。俺は生き残ったんだ。";
			link.l1 = "なぜイッツァ族はお前を助けることにしたんだ？何がそんなに他の奴らと違うんだ？";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "お前には分からねえよ。くそ、俺だって分からなかったさ。誰も俺を助けちゃくれなかった。 昨日のことのように覚えてる……あの野蛮人がカスコの背中から皮をナイフで切り取って、殺してから狂ったように叫び始めた直後、 たぶん俺はあの偶像に吸い込まれたんだ。\n気がついたらテヤサルから遥か遠く、二十年も経っていたのに、ほんの一瞬のことのようだったぜ！";
			link.l1 = "時空の漏斗……くそっ、クサトル・チャの言ったことは全部当たってたじゃねえか！どうやって仮面のことを知ったんだ？ 何のためにそれが必要なんだ？";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			dialog.text = "狂ったインディアンの呪術師によって呼び出された地獄の落とし子を止めねばならん。この忌まわしき存在は、我々 の世界を業火に変えようとしているのだ！";
			link.l1 = "ふむ……ヴィンチェント神父と話したんだな？異端審問官は両方にいい顔をしているってわけか。驚きだな、まったく。で、 俺を探し出して決闘でもしろとでも言われたのか？やるじゃねえか！任務達成だ、ドン・アロンソ！";
			link.l1.go = "ksochitam_8";
		break;
		
		case "ksochitam_8":
			dialog.text = "主は悪との戦いで私の手を強めてくださる。\n私はテヤサルへ戻り、この仮面を使って門を永遠に封じるつもりだ。\nそして、人の姿をしたいかなる悪魔も、二度と我らの世界に足を踏み入れることはない。";
			link.l1 = "ドン・アロンソ、あなたの計画にはひとつだけ小さな問題がある。\n悪魔はすでに我々の中にいるんだ。\n必要なのは、奴をこの門から出さないことだけだ。\nあなたが仮面を奴に渡さなければ、奴はここから出られない。  ";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "そんなものじゃ足りねえ。どっちが正しいにせよ、一つだけ確かなことがある――門は永遠に閉ざさなきゃならねえ。\nその方法はただ一つだ。テヤサルの祭壇にある仮面を破壊すること。\nそうすりゃ、あの悪魔はすべての力を失うはずだ。";
			link.l1 = "ふむ。確かにそれが一番の賭けだな……で、どうやってタヤサルまで行くつもりだ？道は分かっているのか？";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "あの時使った楽な道はもう存在しない。道は石の下に埋もれ、ジャングルの中で失われてしまった。 街へ行く別の道はあるが、それは長くて危険だ。その道はユカタン最北端の入り江から始まる。\nヴィンチェント神父とドン・ラモン・デ・メンドーサの助けを借りて、私は精鋭兵士の部隊を集め、 イツァの野蛮人が守るセルバを力ずくで突破するつもりだ。容易なことではないが、我らの信仰の名のもとに戦う我々に、 神はきっと力と勇気を与えてくださるだろう。";
			link.l1 = "ドン・アロンソ、私の志はあなたの願いと一致しております。この際、しばしわだかまりを脇に置き、手を組みませんか？ \n共に力を合わせれば、この聖戦を成功させる可能性も高まるでしょう。";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "俺はスペイン兵だ。異端者と同盟なんざ結ばんし、フランス野郎と取引もしねえ。\nそれに、ドン・ディエゴのためにお前に復讐を誓ったんだ。命には命で返すぜ！";
			link.l1 = "ドン・アロンソ、あんたは牛みたいに頑固だな！そこに立って「世界が大いなる悪に脅かされている」 と説教してるくせに、そんな途方もない任務を成功させるための俺の助けを断るとはな！";
			link.l1.go = "ksochitam_12";
		break;
		
		case "ksochitam_12":
			dialog.text = "今は俺が決めるんだ、ヴィンチェント神父じゃねえ！\n祈りでも捧げて死ぬ覚悟をしろ、フランスの船長！";
			link.l1 = "ああ、そのセリフはここ数ヶ月で何度も聞いたぜ！構えろ、頑固なカバジェロ！";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_mushketer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_MaldonadoDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			if (MOD_SKILL_ENEMY_RATE > 4) Ksochitam_CreateMaldonadoHelpers();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
