// посредник-дипломат кланов Джузеппе Фацио
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "こんにちは、こんにちは……君はここに来たばかりかい？君の顔は見覚えがないな。自己紹介させてもらおう――俺はジュゼッペ・ファツィオ。この小さな島で問題解決を専門にしているんだ。";
				link.l1 = TimeGreeting()+"。私の名前は "+GetFullName(pchar)+"。おっしゃる通り、私はここでは新参者です。好奇心をお許しください——ですが、あなたはどんな問題を解決しているのですか？";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "ああ、またお前か、旦那 "+pchar.name+"！俺のつましい家に何の用だ？";
				if (CheckAttribute(pchar, "GenQuest.NarvalConflict") || CheckAttribute(pchar, "GenQuest.RivadosConflict") || CheckAttribute(pchar, "GenQuest.SharkConflict"))
				{
					link.l10 = "ファジオ、俺はある一族と深刻な対立があるんだ。この問題を解決しなきゃならねえ。";
					link.l10.go = "conflict";
				}
				// --> квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_3")
				{
					link.l4 = "ジュゼッペ、アドルフ・バルビエという男を探しているんだ。最近、あんたが酒場で奴と飲んでいたと聞いたが……";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && pchar.questTemp.LSC.Drink == "begin")
				{
					link.l5 = "ジュゼッペ、お前は酒に全く酔わないって噂だぜ。どれだけ飲んでも、しっかり立ってるらしいな。";
					link.l5.go = "drink";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && PCharDublonsTotal() >= 100 && pchar.questTemp.LSC.Drink == "wait")
				{
					link.l5 = "俺はお前の勝負に乗るぜ。これが俺の賭け金だ。";
					link.l5.go = "drink_4";
				}
				// <-- квестовые ветки
				if (CheckAttribute(npchar, "quest.parol"))
				{
					link.l1 = "各氏族の領地に入るための現在の合言葉を知りたいんだ。";
					link.l1.go = "parol_choice";
				}
				link.l2 = LinkRandPhrase("何か面白い話でもあるかい？","島で何か新しいことが起きたかい？","最近の噂話を教えてくれないか？");
				link.l2.go = "rumours_LSC";
				link.l3 = "特に用はないさ、ジュゼッペ。ただ会いに来ただけだ。";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "いろんなことをやってるよ、お嬢さん、いろんなことをな。例えば、提督とクランの間をうまく取り持ったりしてる。 もう知ってるかもしれねえが、リバドスとナーワル、そして提督はお互いに敵同士だ。ややこしくなった時は、 俺が仲介役になるんだ。\nそれに、提督がクランに食料を売るときも、よく中立の立場を演じてる。でも、これは俺の仕事のほんの一部さ。だから、 もしリバドスやナーワルで困ったことがあったら、遠慮なく俺に頼ってくれ。何とかできるかもしれねえぜ。";
			link.l1 = "わかった。考えておく。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// пароли
		case "parol_choice":
			dialog.text = "どの一族だ？";
			link.l1 = "ナルバル。";
			link.l1.go = "parol_nrv";
			link.l2 = "リバドス。";
			link.l2.go = "parol_rvd";
		break;
		
		case "parol_nrv":
			dialog.text = "ドナルド・グリーンスパンに会いたいんだろ？";
			link.l1 = "その通りだ。で、合言葉は知ってるか？";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Narwals";
			sTotalTemp = sNrvParol;
		break;
		
		case "parol_rvd":
			dialog.text = "ブラック・エディに会いたいんだろう？";
			link.l1 = "そんなところだ。で、合言葉は知ってるか？";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Rivados";
			sTotalTemp = sRvdParol;
		break;
		
		case "parol":
			if (!CheckAttribute(npchar, "quest.parolrules"))
			{
				dialog.text = "もちろん！だが、その前に詳しい説明をしておこう。合言葉は一語だけで、毎週変わる――つまり、月の7日、14日、21日、28日に新しくなるんだ。\nだから、間違いを防ぐために今の日付をよく確認してくれ。最後に、分かっていると思うが、これは慈善事業じゃない。 合言葉は一つにつきドゥブロン金貨五十枚だ。覚えておけ、支払いはドゥブロンだけだぞ。";
				link.l1 = "50ドゥブロン？それは大金だな！";
				link.l1.go = "parol_1";
			}
			else
			{
				dialog.text = "ああ、坊や。値段は知ってるだろう。五十ドゥブロン持ってるか？";
				if (PCharDublonsTotal() >= 50)
				{
					link.l1 = "ああ。金貨を持っていけ。";
					link.l1.go = "parol_pay";
				}
				link.l2 = "残念だが、今は持っていないんだ。また今度かもな……";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "parol_1":
			dialog.text = "おやおや、坊や、落ち着けよ。欲張るんじゃねえ、俺を信じな。俺は自分の情報の本当の価値を知ってるんだぜ。 お前がただ"+ships+"の船をうろつくだけじゃないってこともな "+pchar.questTemp.LSC.parol+" そうだろ？そうだ。だから、いくらか金貨を失う覚悟が必要だぜ…それで、五十ドゥブロン払う準備はできてるか？";
			if (PCharDublonsTotal() >= 50)
			{
				link.l1 = "ああ。金貨を持っていけ。";
				link.l1.go = "parol_pay";
			}
			link.l2 = "残念だが、そんな金は持ってねえ。もしかしたら後で……";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
			npchar.quest.parolrules = "true";
		break;
		
		case "parol_pay":
			RemoveDublonsFromPCharTotal(50);
			dialog.text = "素晴らしい！取引できて嬉しいぜ。現在の合言葉は "+pchar.questTemp.LSC.parol+" は：「"+sTotalTemp+"「。よく覚えておけ、間違えるんじゃねえぞ。でなきゃ、お前の命に一文たりとも払わねえからな。」";
			link.l1 = "わかってる、わかってる……ありがとう！";
			link.l1.go = "exit";
			AddQuestRecord("LSC", "parol");
			AddQuestUserData("LSC", "sText", pchar.questTemp.LSC.parol);
			AddQuestUserData("LSC", "sParol", sTotalTemp);
			if (pchar.questTemp.LSC.parol == "Rivados") pchar.questTemp.LSC.RParol_bye = "true";
			else pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "adolf":
			dialog.text = "ああ、もちろんだよ、懐かしきアドルフォ！そうさ、彼とは話をしたよ。分かるかい、親愛なる人よ、 私は自分のお金が戻ってきて本当に嬉しかったんだ。もう二度と戻らないと思っていた金だよ！ アドルフォは自慢のライフルを担保にして大金を借りていたが、なかなか返済できずにいたんだ\n私はもう返ってこないと諦めて、そのシュトゥッツェンを愛しきアクセル・ヨストに売ろうとしていた。だが突然、 親愛なるアドルフォが金貨を持ってきてくれたんだ！どうやら彼はシュトゥッツェンを取り戻すだけでなく、『 サンタ・フロレンティナ』号の船首にあるセシル・ガヤールの船室まで買えるほどの金を手に入れたらしい！\nそりゃあ、半分水浸しの船倉で暮らすよりずっといいさ\nだから、アドルフォはライフルも新しい家も手に入れ、私は金を取り戻した。 そんな彼と酒を酌み交わさない理由があるかい？しかも彼のおごりなんだぜ";
			link.l1 = "ああ、もちろんだ！飲む理由はいくらでもあったしな。それにタダで……ありがとう、ジュゼッペ、お前には本当に助けられたぜ。これでアドルフの居場所も分かった。";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "いつでも喜んでお相手するわ、あなた。\nでも、アドルフォを船室で探すのは夕方まで待ったほうがいいわよ、今は何かの用事で忙しく走り回っているから……\nそれと、もっと私のところに遊びに来て。おしゃべりしましょう！";
			link.l1 = "自分の船室を持ったら招待するよ……じゃあな、幸運を祈るぜ！";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			DialogExit();
			LSC_CreateAdolfClone(); // заменяем Адольфа клоном
			pchar.questTemp.Saga.SharkHunt = "search_mush_4"; //флаг на Адольфа в каюте
			AddQuestRecord("SharkHunt", "14");
		break;
		
		case "whiskey":
			switch (sti(npchar.quest.poisonnode))
			{
				case 1: // у себя
					dialog.text = "あぁ？火事でも起きたみたいに俺のところに飛び込んで来て、何様のつもりだ？？";
					link.l1 = "お前の正義か…毒使いめ！";
					link.l1.go = "whiskey_1";
				break;
				
				case 2: // на Эве
					dialog.text = "助けてくれ！誓うよ、無理やりやらされたんだ！奴らが銃を俺の…";
					link.l1 = "黙れ。それは分かってる。最後の野郎はどこだ？マルチェロ・サイクロプスはどこにいる！？";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
				
				case 3: // у Акулы
					dialog.text = "誓います、無理やりやらされたんです！もう提督には全部話しました！逆らえなかったんです、奴らは……";
					link.l1 = "黙れ。そんなことは分かってる。最後の野郎はどこだ？マルチェロ・サイクロプスはどこにいる！？";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
			}
		break;
		
		case "whiskey_1":
			dialog.text = "な…なんだって？";
			link.l1 = "全部知ってるぜ、この野郎。お前はチャド・カッパーと組んでたな。提督に毒入りのラム酒の樽を持ち込んだんだろう。 さあ、祈るんだな、この哀れなクズが……";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "待ってくれ！やめて！命だけは助けてくれ！誓うよ、無理やりやらされたんだ！奴らが銃を俺の…";
			link.l1 = "黙れ。そんなことは分かってる。最後の野郎はどこだ？マルチェロ・サイクロプスはどこにいる！？";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "俺…俺…俺にはわからねえ！";
			link.l1 = "嘘をついてやがるな、このクズめ！見りゃわかるんだよ。サイクロプスはどこだ？";
			if (pchar.questTemp.LSC.Mary == "die") link.l1.go = "whiskey_10"; // ушел на Флерон
			else link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "あいつ…カッパーから何か命令を受けて、どこかへ行っちまったんだ。どこにいるのか俺には分からねえ！";
			link.l1 = "また嘘をついてやがるな。全部知ってるくせに。臆病者になるな、この汚ねえ野郎――カッパーは死んだ、もうお前に危害は加えねえ。だが、マルチェロの居場所を言わねえなら、 今すぐ豚みてえにぶっ殺してやるぞ！チャドはサイクロプスに何を命じたんだ？";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "奴はあいつを送り込んだ……赤毛のメアリーを殺すためにな。";
			link.l1 = "「何だと！？早く言え、どうやってそんなことをするつもりなんだ？あいつの船室に入るなんて不可能だろう！ どうやって彼女を殺すつもりなんだ！？」";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			dialog.text = "鍛冶屋が外に出ている間に、彼はユルゲンの船室に忍び込むんだ。それから船倉の底まで移動し、 そこを横切ってメアリーの船室にたどり着く。\nあとは、あの娘が背を向けるか眠りにつくのを待つだけだって。チャドがそう言ってたんだ。 俺はそれ以上は何も知らない、誓うよ！";
			link.l1 = "それで十分だ。いつ行ったんだ？いつだ、聞いてるんだぞ、サイクロプスは「ケレス鍛冶場」へいつ行った？";
			link.l1.go = "whiskey_7";
		break;
		
		case "whiskey_7":
			dialog.text = "やつはもうユルゲンの船室にいるはずだ…それか船倉の下かもな…";
			link.l1 = "くそっ！島の周りを泳いでる暇なんてねえんだ！ナーヴァルの船の合言葉を教えろ！しゃべれ、もし嘘をついたら、 俺はどうにか生き延びるが、お前は確実に死ぬぞ！";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "「」"+sNrvParol+"「……」";
			link.l1 = "了解だ。あの娘が生き延びるよう祈るんだな。";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "whiskey_repeat";
			pchar.quest.LSC_RescueMary.win_condition.l1 = "location";
			pchar.quest.LSC_RescueMary.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_RescueMary.function = "LSC_RescueMary";
			AddQuestRecord("SharkHunt", "46");
			AddQuestUserData("SharkHunt", "sParol", sNrvParol);
			pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "whiskey_repeat":
			dialog.text = "俺はもう知ってることは全部話したんだ！誓うぜ！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "whiskey_repeat";
		break;
		
		case "whiskey_10":
			dialog.text = "「奴は……奴は『フレロン』の中にいるはずだ。チャドがそこに隠れて次の指示を待てと命じたんだ。」";
			link.l1 = "そうか。真実であってもらわねえとな……";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.LSC_FindCyclop.win_condition.l1 = "location";
			pchar.quest.LSC_FindCyclop.win_condition.l1.location = "FleuronTavern";
			pchar.quest.LSC_FindCyclop.function = "LSC_SetCyclop_Fl";
			NextDiag.CurrentNode = "whiskey_repeat";
			AddQuestRecord("SharkHunt", "51");
			
		break;
		
		// --> конфликты
		case "conflict":
			dialog.text = "そうかい？で、坊や、どの一族があんたを困らせてるんだ？";
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				link.l1 = "ナーワル族。";
				link.l1.go = "narval";
				npchar.quest.clan = "narval";
			}
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				link.l2 = "リバドス。";
				link.l2.go = "rivados";
				npchar.quest.clan = "rivados";
			}
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				link.l3 = "提督の海賊たち。";
				link.l3.go = "shark";
				npchar.quest.clan = "shark";
			}
			link.l4 = "そんなことないさ。冗談だよ、ジュゼッペ、俺は大丈夫だ。";
			link.l4.go = "exit";
		break;
		
		case "narval":
			npchar.quest.price = sti(pchar.GenQuest.NarvalConflict)*50;
			if (sti(pchar.GenQuest.NarvalConflict) < 3) dialog.text = "まあ、争いってほどじゃなくて、ちょっとした誤解さ、へへ。 "+sti(npchar.quest.price)+"  ドゥブロン金貨があれば、お前の問題なんざ一日で解決するぜ。";
			else
			{
				if (sti(pchar.GenQuest.NarvalConflict) >= 3 && sti(pchar.GenQuest.NarvalConflict) < 10) dialog.text = "ああ、その話は聞いたよ。あんた、ずいぶん騒ぎを起こしたじゃねえか、旦那。だが、抜け道はあるぜ。 "+sti(npchar.quest.price)+" ドブロン金貨を出せば、お前の問題は一日で解決するぜ。";
				else dialog.text = "お前がやった虐殺のことは島中に知れ渡ってるぜ。助けるのは簡単じゃねえが、可能性はある。 "+sti(npchar.quest.price)+" ドゥブロン金貨をくれれば、お前の問題を解決してやるぜ。";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "ほら、これが金貨だ。自分で何とかしろ。";
				link.l1.go = "pay";
			}
			link.l2 = "残念だが、今はドゥブロン金貨が足りねえんだ。\nだが後で必ず持ってくるから、その時また話そうぜ。";
			link.l2.go = "exit";
		break;
		
		case "rivados":
			npchar.quest.price = sti(pchar.GenQuest.RivadosConflict)*50;
			if (sti(pchar.GenQuest.RivadosConflict) < 3) dialog.text = "まあ、争いってほどじゃねえさ、ちょっとした行き違いだよ、へへ。 "+sti(npchar.quest.price)+"  ドゥブロンを出せば、お前の問題は一日で解決するぜ。";
			else
			{
				if (sti(pchar.GenQuest.RivadosConflict) >= 3 && sti(pchar.GenQuest.RivadosConflict) < 10) dialog.text = "ああ、それについては聞いたことがあるよ。ずいぶん派手にやらかしたな、あんた。でも抜け道はあるんだ。 "+sti(npchar.quest.price)+"  ドブロン金貨を出せば、お前の問題は一日で解決するぜ。";
				else dialog.text = "お前がやった虐殺のことは島中に知れ渡っている。助けるのは簡単じゃねえが、可能性はあるぜ。 "+sti(npchar.quest.price)+" ドゥブロン金貨をくれれば、お前の問題を解決してやるぜ。";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "ほら、これが金貨だ。自分で何とかしろ。";
				link.l1.go = "pay";
			}
			link.l2 = "残念ながら、今はドゥブロン金貨が足りないんだ。しかし後で持ってくるから、その時また話そう。";
			link.l2.go = "exit";
		break;
		
		case "shark":
			npchar.quest.price = sti(pchar.GenQuest.SharkConflict)*50;
			if (sti(pchar.GenQuest.SharkConflict) < 3) dialog.text = "まあ、争いってほどじゃなくて、ちょっとした誤解さ、へへ。 "+sti(npchar.quest.price)+" ドゥブロン金貨を出せば、お前の問題は一日で解決するぜ。";
			else
			{
				if (sti(pchar.GenQuest.SharkConflict) >= 3 && sti(pchar.GenQuest.SharkConflict) < 10) dialog.text = "ああ、それについては聞いたことがあるよ。ずいぶんと騒ぎを起こしたね、君。だが、抜け道はあるんだ。 "+sti(npchar.quest.price)+" ドブロン金貨があれば、お前の問題なんざ一日で解決するぜ。";
				else dialog.text = "お前がやった虐殺のことは島中に知れ渡ってる。手を貸すのは簡単じゃねえが、可能性はあるぜ。 "+sti(npchar.quest.price)+" ドブロン金貨をくれれば、お前の問題を解決してやるぜ。";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "ほら、これが金貨だ。自分で何とかしろ。";
				link.l1.go = "pay";
			}
			link.l2 = "残念だが、今はドゥブロン金貨が足りないんだ。\nだが後で持ってくるから、その時また話そうぜ。";
			link.l2.go = "exit";
		break;
		
		case "pay":
			RemoveDublonsFromPCharTotal(sti(npchar.quest.price));
			PlaySound("interface\important_item.wav");
			Log_Info("You have given "+sti(npchar.quest.price)+" doubloons");
			dialog.text = "素晴らしい。さあ、席について休んでくれ。私が君の問題を解決するまで、私の船室にいた方がいい。 これ以上事態を悪化させてほしくないんだよ、坊や。";
			link.l1 = "……わかった……";
			link.l1.go = "peace";
		break;
		
		case "peace":
			DialogExit();
			GetCharacterPos(pchar, &locx, &locy, &locz);
			pchar.locx = locx;
			pchar.locy = locy;
			pchar.locz = locz;
			SetLaunchFrameFormParam("One day later..."+ NewStr() +"Fazio has dealt with the conflict", "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
			WaitDate("", 0, 0, 1, 3, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			switch (npchar.quest.clan)
			{
				case "narval":
					DeleteAttribute(pchar, "GenQuest.NarvalConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") || !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);//открыть вход к Дональду
					LAi_group_SetRelation("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "rivados":
					DeleteAttribute(pchar, "GenQuest.RivadosConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend") || !CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload33", false);//открыть вход к Эдди
					LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "shark":
					DeleteAttribute(pchar, "GenQuest.SharkConflict"); // мирим
					LSC_OpenSanAvgustinDoors(); // открыть сан-августин
					LSC_OpenTartarusDoors(); // открыть тартарус
					LAi_group_SetRelation("LSC_SHARK", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
			}
			DeleteAttribute(npchar, "quest.clan");
			DeleteAttribute(npchar, "quest.price");
		break;
		
		// --> пей до дна
		case "drink":
			dialog.text = "さあ、坊や！あいつらはみんな嘘つきだぜ、へへ。俺の頭がちょっと人より頑丈なだけで、俺だってお前と同じ人間さ。 ラム酒を飲めば酔っぱらうさ。人は酔うためにラムを飲むんだ、それが唯一の目的だろ。お前も考えたことあるかい、 坊や？";
			link.l1 = "まったくその通りだ。";
			link.l1.go = "drink_1";
		break;
		
		case "drink_1":
			dialog.text = "俺と面白い遊びをやりたいか？その名も「最後の一滴まで飲み干せ！」だぜ、はは！もう聞いたことあるだろ？ そうじゃねえか？";
			link.l1 = "ああ、その噂は少し聞いたぜ……俺は「テーブルに顔を伏せる」って呼んでるがな。";
			link.l1.go = "drink_2";
		break;
		
		case "drink_2":
			dialog.text = "ハハハ、坊や、お前のおかげでじじいは久々に笑ったぞ、他に何を言えばいいんだ！「顔をテーブルに！」か……覚えておくぜ……で、どうする？百ドゥブロンで勝負するか？";
			link.l1 = "百ドゥブロンだと？";
			link.l1.go = "drink_3";
		break;
		
		case "drink_3":
			dialog.text = "ああ、負けた方が酒代を払うってことでいいか？どうだ？";
			if (PCharDublonsTotal() >= 100)
			{
				link.l1 = "ああ、取引成立だ。これが俺の賭け金だ。";
				link.l1.go = "drink_4";
			}
			link.l2 = "ふむ。そんなに多くのドゥブロン金貨は持っていないな。";
			link.l2.go = "drink_wait";
		break;
		
		case "drink_wait":
			dialog.text = "じゃあ、それを手に入れたら俺のところに来いよ、一緒に遊ぼうぜ！";
			link.l1 = "……わかった……";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Drink = "wait";
		break;
		
		case "drink_4":
			RemoveDublonsFromPCharTotal(100);
			Log_Info("You have given 100 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "素晴らしいわ、坊や！それじゃ、夜九時にサンチョの酒場で会いましょう！\nええ、もし遅れたら賭け金は私が預かるわよ、それがルールの一つなの。\nでも、遅れたりしないでしょう、坊や？";
			link.l1 = "ああ、ジュゼッペ。瓶の戦いに備えろよ！";
			link.l1.go = "drink_5";
		break;
		
		case "drink_5":
			dialog.text = "「お前もだ、お前もだ、俺の可愛い奴！顔をテーブルにつけろ！ははっ！」";
			link.l1 = "九時に酒場で会おうぜ！";
			link.l1.go = "drink_6";
		break;
		
		case "drink_6":
			DialogExit();
			pchar.questTemp.LSC.Drink = "start";
			pchar.quest.LSC_DrinkOver.over = "yes"; //снять таймер
			pchar.quest.LSC_Drink.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink.win_condition.l1.date.hour  = 21.0;
			pchar.quest.LSC_Drink.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink.function = "LSC_DrinkPrepare";
			pchar.quest.LSC_Drink_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.hour  = 23.0;
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink_Over.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "2");
		break;
		
		case "drink_8":
			dialog.text = "さて、あんた、準備はいいかい？テーブルにキスする覚悟はできてるか、へへ？ サンチョの奴がもうラムを持ってきてくれたぜ。ルールなんざ説明いらねえよな？簡単なもんさ――同じ瓶から飲み続けて、どっちかが潰れるまでだ。\nそうさ、話してもいいし、むしろ話そうじゃねえか！まともな奴と語るのは最高だろ？もし勝ったら、 サンチョから賞品をもらえるぜ。準備はいいか？";
			link.l1 = "そうだな。始めようぜ、ジュゼッペ！";
			link.l1.go = "drink_9";
		break;
		
		case "drink_9":
			DialogExit();
			pchar.questTemp.LSC.Drink = "go";
			pchar.quest.LSC_Drink_Over.over = "yes"; //снять таймер
			ChangeCharacterAddressGroup(pchar, "FleuronTavern", "quest", "sit1");
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			ChangeCharacterAddressGroup(npchar, "FleuronTavern", "quest", "sit2");
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			DoQuestFunctionDelay("LSC_DrinkGo", 0.6);
		break;
		
		case "drunk":
			dialog.text = "死者の上に十五人……ひっく！あはは！ヨーホーホー……それから……瓶……";
			link.l1 = "「栄光の……」";
			link.l1.go = "exit";
			NextDiag.TempNode = "drunk";
		break;
		// <-- пей до дна
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
