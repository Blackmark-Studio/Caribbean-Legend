// Чад Каппер - боцман Акулы и тюремщик
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
			dialog.text = "何か用か？";
			link.l1 = "いや、何もない。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// вариант R
		case "Chimiset":
			dialog.text = "ほうほう……お前が噂の謎の盗人か？ふむ……普通のコソ泥には見えねえな。";
			link.l1 = "旦那、勘違いしてるぜ。俺はここに来たばかりなんだ、 だからあんたの連中が俺を捕まえたあの貨物倉庫があんたの持ち物だなんて知るわけないだろう？";
			link.l1.go = "Chimiset_1";
		break;
		
		case "Chimiset_1":
			dialog.text = "へえ、そうかい？いい線いってるじゃねえか、相棒……で、どこからここへ来たんだ？";
			link.l1 = "スペイン領本土から、インディアンの偶像を通って……どう説明すればいいのか、うまく言えねえんだ……";
			link.l1.go = "Chimiset_2";
		break;
		
		case "Chimiset_2":
			dialog.text = "像か？ははっ！お前、面白い奴だな…？じゃあ俺が当ててやろう。お前は船の船体に空いた穴を泳いで通って、俺たちの倉庫に忍び込んだんだろ？だが、 どうしてお前の顔を見覚えがねえんだ？俺はリヴァドスの連中は全員知ってるんだが…";
			link.l1 = "リバドス？何のことか全然わからねえ！聞いてくれ、俺はここに来たのはほんの一時間前なんだ――";
			link.l1.go = "Chimiset_3";
		break;
		
		case "Chimiset_3":
			dialog.text = "大声を出すな、俺は耳が遠くねえんだ。いや、お前のふざけた態度は笑えるが、しばらくそのまま放っておくとしよう。\nネズミに足の指でもかじられたら、少しは考えが変わるかもな。";
			link.l1 = "リバドスのことなんて何も知らねえ！俺の名はシャルル・ド・モールだ！";
			link.l1.go = "Chimiset_4";
		break;
		
		case "Chimiset_4":
			dialog.text = "ふむ……お前の言うことは本当かもしれねえな……リヴァドスは白人と組むような連中じゃねえ。はっきり答えろ……お前はあいつらの仲間か？";
			link.l1 = "誓って言うが、その名前は今まで聞いたことがねえ！俺は誰とも組んじゃいねえんだ！";
			link.l1.go = "Chimiset_5";
		break;
		
		case "Chimiset_5":
			dialog.text = "本当か？よし、証明してみろ。下に行け、檻の中にリバドスが座ってる。あいつは危険な魔術師だ。そいつを殺せば、 俺も納得するぜ。\nそれに、お前が倉庫に勝手に入ったことも水に流してやる。どうする？怖がるなよ、魔術師は武器も持ってねえし、 弱ってる。まあ……呪文でお前を塵に変えるかもしれねえけどな、へへ……";
			link.l1 = "俺が見てきたものをお前が見てたら、冗談なんか言えねえさ――";
			link.l1.go = "Chimiset_6";
		break;
		
		case "Chimiset_6":
			dialog.text = "よし、もういい！やるのかやらねえのか？やるならこのマチェーテを持ってあの魔術師を斬れ。 そうしねえとタルタロスの底で死ぬことになるぜ。わかったか？";
			link.l1 = "…マチェーテを渡してくれ。";
			link.l1.go = "Chimiset_7";
		break;
		
		case "Chimiset_7":
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "slave_02");
			EquipCharacterbyItem(pchar, "slave_02");
			dialog.text = "いい子だ。さあ、あの黒人のブードゥー使いを殺してこい。檻の鍵は開いてるぞ。下手な真似はするなよ――逃げようなんて考えたら、すぐにでもお前を始末するからな。さあ、行け！";
			link.l1 = "この錆びたガラクタでお前らをぶった斬るのが怖いってか？";
			link.l1.go = "Chimiset_8";
		break;
		
		case "Chimiset_8":
			dialog.text = "俺の我慢も限界だぜ、相棒。貨物倉に行って、言われた通りにしろ！";
			link.l1 = "わかった、わかった、今行くよ……";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//разлочим Ф2
		break;
		
		case "Chimiset_9":
			dialog.text = "俺の我慢も限界だぜ、この野郎！俺を怒らせたくねえだろう…";
			link.l1 = "い、いいから、落ち着け。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
		break;
		
		case "Fightfail_Final":
			dialog.text = "黒人を殺したのか？よし……それは嬉しいぜ。お前がリヴァドスじゃねえって証明したな。";
			link.l1 = "やっとこの忌々しい箱舟から解放されるのか？すぐにシャーク・ドドソンに会わなきゃならねえ。";
			link.l1.go = "Fightfail_Final_1";
		break;
		
		case "Fightfail_Final_1":
			dialog.text = "地獄への道で……あいつに会うことになるさ。";
			link.l1 = "……くそっ。";
			link.l1.go = "Fightfail_Final_2";
		break;
		
		case "Fightfail_Final_2":
			DialogExit();
			DoQuestCheckDelay("LSC_ChadGuardAttack_Fail", 0.1);
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "はっ！見ろよ、これ。俺の牢屋で何してやがるんだ？";
			link.l1 = "お前の名前はチャド・カッパーだろ？俺は "+GetFullName(pchar)+"「……シャーク・ドドソンの使いで来たんだ。鍵は彼から預かった。」";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "提督があんたを寄越したのか？ふん。あんたはあいつの新しい使い走りか？";
			link.l1 = "言葉に気をつけろ、旦那……さもねえと舌を失うぜ。俺は誰の使い走りでもねえ。";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "ははっ！お前、気に入ったぜ、相棒。今の話は忘れてくれよ……で、ここで何の用だ？";
			link.l1 = "シャークがチミセットを解放するよう命じた。";
			link.l1.go = "prisoner_3";
		break;
		
		case "prisoner_3":
			dialog.text = "リバドスのブードゥー使いか？ふむ、妙だな……それを聞いて本当に驚いたぜ……";
			link.l1 = "シャークはリヴァドスと和解したがっている。";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "あ、ああ、そうか……わかった。リバドスに使いを出すぜ。奴らが自分たちの魔術師を迎えに来ればいいさ。";
			link.l1 = "なぜ彼をただ解放できないんだ？";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "もちろんできるさ……だが、奴を殺したいならな。チミセットはこの辺りじゃ有名だ。奴がエスメラルダ号の甲板――つまり敵であるナーワルの縄張り――に足を踏み入れた瞬間、命はないだろう。\nタルタロスを出るには他に道はないし、あの爺さんに島を泳がせるわけにもいかねえ！もし奴に何かあれば、 リヴァドスが俺たち――特に俺を――責めるに決まってる！\nそんな面倒ごとはごめんだ。だから、奴の一族が自分で安全を保証するなら解放してやる。 チミセットに直接話したいのか？あいつはなかなか面白い奴だぜ……";
			if (CheckAttribute(npchar, "quest.chimiset_talk")) link.l1 = "もう彼とは話したよ。確かに変わった奴だな……さて、行かなくちゃ。じゃあな、チャド。";
			else link.l1 = "そのつもりだ。今から会いに行く。";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			DialogExit();
			sld = characterFromId("Chimiset");
			sld.quest.capper_talk = "true"; // разговор с Каппером состоялся
			if (!CheckAttribute(npchar, "quest.chimiset_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "リバドスに使いを出して、あいつらが自分の呪術師を引き取りに来るさ。心配すんな、相棒、お前は行っていいぜ。";
			link.l1 = "「わかった。」";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_7";
		break;
		
		// вариант M
		case "Aeva_attack":
			dialog.text = "…もう樽を開けてるはずだ、間違いねえ。あいつのお気に入りのウイスキーさ、ブッシュミルズ。もうすぐ終わるぜ、 あの樽には象でも死ぬほどのヒ素を入れておいたからな…";
			link.l1 = "";
			link.l1.go = "Aeva_attack_1";
			CharacterTurnToLoc(npchar, "quest", "quest2");
		break;
		
		case "Aeva_attack_1":
			dialog.text = "ん？くそっ、何しに来やがった！？消えろ！";
			link.l1 = "探してたぜ、毒使い。妙だな、サイクロプスが見当たらねえ……シャークの地位を狙ってたんだろ？";
			link.l1.go = "Aeva_attack_2";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Aeva_attack_2":
			dialog.text = "ははっ、シャークはもう死んじまってるだろうよ！そしてお前もすぐにあいつの後を追うことになるぜ、間者め！";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Aeva_attack_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("ChadNarval_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CapperDieAeva");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Aeva_attack_2":
			dialog.text = "…こりゃあ、とんでもねえ酒盛りになりそうだぜ。シャークはこのウイスキーをどれだけ夢見てきたことか、 一気に飲み干すに決まってる。ヒ素はどこだ？念のため二本使おうじゃねえか……それから、この樽をファジオが提督に「ナーワルからの贈り物」って届けりゃいい、ははは！\nなあ、ジュゼッペ。元気出せよ、坊主。うまくやりゃ心配なんていらねえ――おっと！お客さんだぜ、野郎ども！何の用だ、間抜け？ここは内輪の集まりなんだよ。";
			link.l1 = "カッパー、お前の計画は失敗したぜ。お前と仲間のマルチェロが何を企んでいるか、もう知ってるんだ。ヒ素を捨てろ！ シャークを毒殺なんてさせねえぞ！";
			link.l1.go = "Aeva_attack_3";
		break;
		
		case "Aeva_attack_3":
			dialog.text = "ああ、くそっ。よし……まずはお前が死ぬんだ、それからシャークだ！武器を取れ、野郎ども！";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
