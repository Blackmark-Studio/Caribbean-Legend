// лидер клана ривадос - Чёрный Эдди
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
			dialog.text = "「リバドスの縄張りで何してるんだ、白人？」";
			link.l1 = "地元の連中とちょっと顔を合わせてただけさ。邪魔したんなら悪かったな。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Friend":
			dialog.text = "リバドスの友人であり、しかも善良な男を迎えられて嬉しいぜ！チミセットからあんたがしてくれたことは聞いてる。 リバドスの皆、俺も含めて、今やあんたに借りができたな。自己紹介させてもらうぜ――エドワード・ブラック、通称ブラック・エディ、リバドス団の頭だ。";
			link.l1 = ""+GetFullName(pchar)+"…。まあ、チミセットがもう俺のことを話したんじゃねえかと思うぜ。あいつ、お前に伝えるって約束してたからな…";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			dialog.text = "そして彼はやってくれた。これで俺たちの船を自由に訪ねていいぜ。見張りも止めやしねえし、 俺たちもあんたに会えて嬉しいさ。\nただしナーワルどもには気をつけろよ。チミセットを助けたことはもう奴らの耳にも入ってるはずだし、 あいつらは気に入らねえだろうからな、俺たちは敵同士だからよ。";
			link.l1 = "考えておくよ。温かく迎えてくれてありがとう、エディ！さて、チミセットと話をさせてくれ。";
			link.l1.go = "Friend_2";
		break;
		
		case "Friend_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			AddSimpleRumourCityTip("They say that you are a close friend of Black Eddie, the head of Rivados. How did you do this?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Rivados claim you as their friend. How'd you do it?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that the Narwhals have a price on your head. Are you scared?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		// --> информационный блок
		case "Total_info": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "白い兄弟か？生きていたのか？嬉しいぞ！じゃあ、ナーワルどもがみんなにお前は溺れ死んだと嘘をついたんだな……";
				link.l1 = "俺も会えて嬉しいぜ、エディ。俺の死の噂は大げさに広まってるだけさ。";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "会えて嬉しいよ。 "+pchar.name+"……何か新しい知らせはあるか？";
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l1 = "エディ、この島にナサニエル・ホークという男を知ってるか？俺の知る限り、ここにいるはずなんだ。";
				link.l1.go = "natan";
			}
			if (!CheckAttribute(npchar, "quest.rivados"))
			{
				link.l2 = "リバドスの一味についてもっと教えてくれ。";
				link.l2.go = "rivados";
			}
			link.l9 = "別に特別なことはないさ。本当に、ちょっと挨拶したかっただけだ。";
			link.l9.go = "exit";
		break;
		
		case "natan":
			dialog.text = "ナサニエル・ホーク？いや、その男は知らねえな。リバドスの船にもいねえし、中立地帯にもいねえ。\nナーワルの連中については同じことは言えねえがな。俺たちはあいつらのところには行かねえんだ。";
			link.l1 = "なるほど……";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_info";
		break;
		
		case "rivados":
			dialog.text = "リバドス団は何年も前に結成された。この見捨てられた船の街で最初にできたクランだ。五十年以上前、 西アフリカからベタンコート提督の遠征隊が、いくつもの大型奴隷船と共にここへ航海してきた。 タルタロス号の船倉には、カリブのプランテーションへ送られる何百人もの黒人奴隷が詰め込まれていた。 その奴隷の中にペドロ・リバドスという男がいた。彼はポルトガル人の神父たちから読み書きを教わっていた。\n彼は数十人の奴隷を鎖から解放し、反乱を起こすことに成功した。だが、 残りの奴隷たちは彼に加わることができなかった。反乱は鎮圧され、 奴隷商人たちはリバドスを手足を縛って船倉に放置し、飢えと渇きで死ぬに任せた。数日後、天候が荒れ、 ベタンコートの艦隊は強烈な嵐に巻き込まれた。\n数日後、嵐と戦った末に、無事だったのはサン・アウグスティン号とタルタロス号の二隻だけで、 この正義の島の真ん中に取り残された。その出来事で多くの者が命を落とした。黒人も白人も。しかし、 さらに多くの者が生き延びた。元奴隷たちは新たな人生を共に始め、 解放者ペドロ・リバドスに敬意を表して自らをリバドスと名乗った。";
			link.l1 = "とても興味深い話だな……ありがとう！";
			link.l1.go = "exit";
			npchar.quest.rivados = "true";
			NextDiag.TempNode = "Total_info";
		break;
		// <-- информационный блок
		
		case "capper":
			dialog.text = "「リバドスの領地で何の用だ、白人？」";
			link.l1 = "私の名前は "+GetFullName(pchar)+" そして俺はドッドソン提督の命令でここに来たんだ。ブラック・エディと話さなきゃならねえ。俺の理解では、 それがあんただろう。";
			link.l1.go = "capper_1";
		break;
		
		case "capper_1":
			dialog.text = "ああ、俺がエドワード・ブラック、通称ブラック・エディだ。で、提督は俺に何の用だ。";
			link.l1 = "「タルタロス」にチミセットという男がいる。提督は彼を解放するつもりだ。";
			link.l1.go = "capper_2";
		break;
		
		case "capper_2":
			dialog.text = "これはとても良い知らせだ。チミセットは俺たちリヴァドスの精神的指導者で、みんな彼を恋しく思っているんだ。\nだが、提督は彼の解放と引き換えに何かを求めているんだろう、違うか？";
			link.l1 = "何もない。ただ善意のしるしとして彼を解放したいだけだ。しかし、問題があるんだ…";
			link.l1.go = "capper_3";
		break;
		
		case "capper_3":
			dialog.text = "行けよ、白人。";
			link.l1 = "かつて提督の甲板長だったチャド・キャッパーは、今や牢番となり、ナーワルの一員として裏切り者に転じ、 提督の手に負えなくなっている。\nチャドがチミセットを殺す計画を立てていることは我々も知っている。提督はそれを望んでいない。\n裏切り者を排除し、あなたの仲間を解放するため、共同作戦を提案したい。";
			link.l1.go = "capper_4";
		break;
		
		case "capper_4":
			dialog.text = "お前の言葉、ちょっと変だが、続けてくれ。チミセットが困ってるのか？";
			link.l1 = "ああ。チャドは彼を殺すつもりだ。カッパーはナーワル族を使ってこの街を支配しようとしている。 今のうちにチミセットを救いたいなら、急いで行動しなきゃならないぜ。チャドは今のところ何も疑っていない。提督は『 タルタロス』から全ての衛兵を引き上げたから、通路は今なら空いている。これが牢獄の中の扉を開ける鍵だ。 持っていけ。\n";
			link.l1.go = "capper_5";
		break;
		
		case "capper_5":
			RemoveItems(pchar, "key_capper", 1);
			dialog.text = "";
			link.l1 = "仲間を集めて、タルタロスへ行き、キミセを解放しろ。すべての切り札はお前のものだ。";
			link.l1.go = "capper_6";
		break;
		
		case "capper_6":
			dialog.text = "罠の匂いがするな……それに待ち伏せがあるかもしれねえだろ？もし提督がリヴァドスを叩く決断をしたらどうする？ なんで自分でカッパーを始末しねえんだ？\n";
			link.l1 = "ドッドソンは、お前がチミセトの命を気にかけていると言っていた……彼は十分やったさ。これが鍵だ、見張りもいない。あとは中に入ってチャドを片付けて、お前の仲間を解放するだけだ。 罠はないと俺の言葉を信じてくれ。\nああ、それともう一つだけ。提督はチミセトの命と自由の代わりにチャドの首を望んでいる。\nこれで取引成立ってことでいいか？";
			link.l1.go = "capper_7";
		break;
		
		case "capper_7":
			dialog.text = "チミセットの命はリバドスにとって計り知れないほど大切だ。俺たちはすぐに『タルタロス』へ向かう。だが、 お前は人質としてここに残ってもらうぜ。もし待ち伏せがあれば、リバドスの怒りを受けることになるぞ！\nジコモ！扉のそばにいて、客人を見張れ。絶対に外に出すな。俺が自ら『タルタロス』への攻撃を指揮する！";
			link.l1 = "幸運を祈るぜ、エディ。\nそれと忘れるな、俺が欲しいのはチャド・カッパーの首だ！";
			link.l1.go = "capper_8";
		break;
		
		case "capper_8":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_ZikomoNearDoor", 10.0);
			NextDiag.CurrentNode = "chimiset";
		break;
		
		case "chimiset":
			dialog.text = "チミセットが解放された！嘘じゃなかったな、白人よ、これでお前をリバドスの友と呼ぶ準備ができたぜ！";
			link.l1 = "嬉しいよ。チャド・カッパーは死んだのか？";
			link.l1.go = "chimiset_1";
		break;
		
		case "chimiset_1":
			dialog.text = "許しを請わねばならぬ、白い友よ。お前は俺たちのためにできる限りのことをしてくれたのに、 俺たちはお前を裏切ってしまった……俺が、お前を裏切ったんだ！あの忌々しいカッパーは逃げおおせた。奴のそばにはナーワルの連中が二人いた。 そいつらは仕留めたが、あの汚い看守は下の扉からナーワルの領地へ泳いで逃げやがった。";
			link.l1 = "くそっ……「タルタロス」には出口が二つあるって知らなかったのか？";
			link.l1.go = "chimiset_2";
		break;
		
		case "chimiset_2":
			dialog.text = "考えてなかったんだ。正面入口から攻め込んだんだよ…";
			link.l1 = "残念だな。奴の首を当てにしてたんだぜ。惜しいことだ。これでまた俺たちに逆らい続けるってわけか。";
			link.l1.go = "chimiset_3";
		break;
		
		case "chimiset_3":
			dialog.text = "俺の非を認めるぜ。だが、あいつを敵の船まで追うことはできなかった。チャドの首の代わりに、 俺たちの友情と敬意を受け取ってくれ。これからは、俺たちの領地を自由に訪れていいぞ。 チミセットの知恵もきっと役に立つはずだ、何かあれば彼に相談しな。あと、 提督には俺が彼の行動を評価していると伝えてくれ。";
			link.l1 = "「いいだろう。」";
			link.l1.go = "chimiset_4";
		break;
		
		case "chimiset_4":
			dialog.text = "待て！チャドは失ったが、奴の机の上にいくつか書類があった。俺たちが来た時、あいつが調べてたやつだ。\nほら、これだ。役に立つかもしれねえぜ、白い兄弟よ。";
			link.l1 = "はっ！もしかして……チャドは紙切れをずいぶん信じてるんだな……";
			link.l1.go = "chimiset_5";
		break;
		
		case "chimiset_5":
			dialog.text = "ここではいつでも歓迎される客人だぜ、白い友よ。リバドスの皆にも伝えておく。幸運を祈るぜ！";
			link.l1 = "「エディ、お前もな……」";
			link.l1.go = "chimiset_6";
		break;
		
		case "chimiset_6":
			DialogExit();
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			sld = CharacterFromID("Zikomo");
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, true);
			GiveItem2Character(pchar, "letter_chad");
			ChangeItemDescribe("letter_chad", "itmdescr_letter_aeva");
			GiveItem2Character(pchar, "letter_chad_1");
			ChangeItemDescribe("letter_chad_1", "itmdescr_letter_axel");
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			pchar.questTemp.Saga.SharkHunt = "dodson_whiskey"; // к Акуле
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "Chad_escape"; // ноду Акуле
			AddQuestRecord("SharkHunt", "33");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true); // закрыть вход к Дональду Гринспи
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Have you heard the latest news? The Rivados' insolence is out of control, they have attacked the admiral's prison and released their wizard!", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("Just think about it - those uppity Rivados dared to attack the 'Tartarus'! They say that the jailer, Chad Kapper, has escaped to the Narwhals...", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("This is the height of impudence, isn't it? Attacking a military facility of the admiral! Aye, looks like Black Eddie is getting stronger...", "LostShipsCity", 3, 2, "LSC", "");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
