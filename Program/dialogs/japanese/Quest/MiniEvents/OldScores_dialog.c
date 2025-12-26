void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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

		case "OS_Matros_sluh":
			bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			if (bOk1 || bOk2)
			{
				dialog.text = "昨夜、酒場で乱闘があったらしい……だが、誰が喧嘩してたのかなんて、俺にはさっぱりわからねえ。俺の顔はまだ無事だ。たぶんな。";
				link.l1 = "ここはずいぶんと酒盛りがあったみてえだな？";
				link.l1.go = "OS_Matros_sluh_2";
			}
			else
			{
				switch (rand(2))
				{
					case 0:
						dialog.text = "「おい、」 "+GetSexPhrase("相棒","娘")+"「俺のブーツ、どこかで見なかったか？酒場のテーブルの下で酔いつぶれてる間に、 どこかのクソ野郎に盗まれちまったんだ。」";
						link.l1 = "もっと注意して見張れよ、さもないともう片方の目も同じ目に遭うぜ。";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 1:
						dialog.text = "昨日酒場で乱闘があったって噂だ……だが誰が喧嘩してたのかは誰にも分からねえ。俺の顔は無事みたいだ。たぶんな。";
						link.l1 = "もしかすると、お前の面はもう十分にやられてると奴らは思ったんじゃねえか。";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 2:
						dialog.text = "地獄の悪魔どもにかけて、昨日は金貨でいっぱいの財布を持ってたんだぜ！今はいったいどこに消えやがったんだ！？";
						link.l1 = "本物の海賊にとって、一番大事なのは金じゃねえ。\n自由こそが何よりも価値があるんだぜ。";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;
				}
			}
		break;
		
		case "OS_Matros_sluh_2":
			dialog.text = "ああ、間違いねえよ！宿屋の親父はてんてこ舞いだったぜ…ひっく…それに加えてよ…誰かが奴のジンを盗みやがったんだ！瓶一本じゃねえ、丸ごと樽一本だ！しかもただの樽じゃねえ――カリブ中探したって見つからねえ代物さ！ヨーロッパからわざわざ運ばれてきたって話だ。誰のためかは口を割らねえが、 一つだけ確かなのは――あれが早く見つからなきゃ、あの親父にとっちゃ嵐みてえな災難が待ってるってことだな！\n";
			link.l1 = "面白いな。じゃあな、酔っ払いのじじい、元気でな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "OS_Matros_sluh";
			OS_Start();
		break;

		case "OS_Matros_again":
			switch (rand(2))
			{
				case 0:
					dialog.text = "他に何が欲しいんだ？俺の頭蓋骨が今にも割れそうなのが見えねえのか？消え失せろ。";
					link.l1 = "酒を控えれば、酔いどれの廃人じゃなくて、まともな男に見えるかもしれねえぞ。";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "ほっといてくれ……頭が今にも爆発しそうだ！";
					link.l1 = "肩にまだちゃんとくっついてるだけでも大したもんだぜ。";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 2:
					dialog.text = "地獄に落ちやがれ……俺をほっとけ、今は話せる状態じゃねえのがわからねえのか！";
					link.l1 = "...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
		break;
		
		case "OS_Matros":
			dialog.text = "下がれ！俺はもう限界なんだぜ！誰かの顎に拳をぶち込みたくてウズウズしてるんだよ。";
			link.l1 = "落ち着け、水夫。俺はただ昨日の酒場で何があったかを聞きたいだけだ。";
			link.l1.go = "OS_Matros_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Matros_2":
			dialog.text = "くそっ、呪われちまえ！お前は "+GetSexPhrase("あの狂った給仕女のもう一人の恋人","親類")+"？何の用だ、嵐で海に投げ出されちまえってんだ！俺に決闘を挑むつもりか？それとも今ここで刃を抜く気か？";
			if (pchar.sex == "woman")
			{
				link.l1 = "親戚だと？とんでもねえよ。だが、お前さんはあの女をあまり高く評価してねえみたいだな？";
				link.l1.go = "OS_Matros_3_scrit";
			}
			else
			{
				link.l1 = "恋人？とんでもねえよ。あの女は質より量を追い求めてるみたいだぜ、そう思わねえか？";
				link.l1.go = "OS_Matros_3_scrit";
				link.l2 = "あいつのことなんざ俺には関係ねえ。何があったかだけ話せ、そしたらもう邪魔しねえよ。 あんたがあいつをあんなに怒らせたんじゃねえのか？";
				link.l2.go = "OS_Matros_3_fortuna";
			}
		break;
		
		case "OS_Matros_3_scrit":
			dialog.text = "あの女狐は、何ヶ月も海に出て腹を空かせた水夫と同じくらい見境がねえんだ――近くにあるもんをとりあえず掴んで、後でどうにかするってな！\n夕方からずっと俺に色目を使ってきやがって、まるで酒場の猫が残飯を狙ってるみてえにじゃれついてきたんだ。\nだが、いざ俺があの女の港に錨を下ろそうとした瞬間――あいつの叫び声は湾の魚どもを深海に逃げ込ませるほどだったぜ！";
			link.l1 = "もしかして、ラムを飲みすぎて、ちょっと図々しくしすぎたんじゃねえか？";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "OS_Matros_3_fortuna":
			dialog.text = "あの女狐は、何ヶ月も海に出て腹を空かせた水夫と同じくらい見境がねえ――目の前にあるもんをとりあえず掴んで、後でどうにかするってやつだ！\n夕方からずっと俺に色目を使ってきやがって、酒場の猫みてえに媚び売ってたくせによ。\nだが、いざ俺がその港に錨を下ろそうとした瞬間――あいつの叫び声は湾の魚まで深海に逃げ込むほどだったぜ！";
			link.l1 = "もしかして、ラムを飲みすぎて、ちょっと図々しく近づきすぎたんじゃねえか？";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "OS_Matros_4":
			dialog.text = "酒に酔ってたかもしれねえが、あそこで何があったかは凪の海みてえにハッキリ覚えてるぜ。 俺があの女を追いかけてたんじゃねえ、あいつが血の匂いを嗅ぎつけたサメみてえに俺の周りをうろついてたんだ。 あの忌々しい一日中、ずっと俺のそばを離れなかったんだよ！";
			if (pchar.sex == "woman")
			{
				link.l1 = "「そんな些細なことで、最初に会った相手と喧嘩する気だったのか？それとも、その晩に他に何かあったのか？」";
			}
			else
			{
				link.l1 = "聞けよ、「もう一人の恋人」って言ったな。あいつの浮気について何か知ってるのか？";
			}
			link.l1.go = "OS_Matros_5";
		break;

		case "OS_Matros_5":
			dialog.text = "彼女の叫び声が静まった後、仲間たちが言ったんだ。あの女の海で釣り糸を垂れるのは時間の無駄だってな。 町には彼女に言い寄る男がいて、そいつは俺たちの船長とまるでグルらしいぜ。";
			link.l1 = "興味深いな。他に何か変わったことに気づいたか？騒ぎの最中に誰かがカウンターに近づいてきたとか？";
			link.l1.go = "OS_Matros_6";
		break;

		case "OS_Matros_6":
			dialog.text = "くそったれ……頭が岩礁にぶつかった船体みてえに割れそうだってのに、てめえはまたその忌々しい質問かよ。何も見ちゃいねえし、 何も聞いちゃいねえ。こんな尋問でベテラン水夫を苦しめるより、ペソの何枚か恵んでくれたほうがよっぽどマシだぜ。";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "ほら、百ペソだ。いいか、また飲みすぎて酔いつぶれたり、あの給仕娘に惑わされたりするんじゃねえぞ？";
				link.l1.go = "OS_Matros_7_harizma";
			}
			link.l2 = "俺の金がなくてもやっていけるだろう。\nさもなきゃ、どうせまた酔っ払ってあの給仕娘にちょっかい出すだけだぜ。";
			link.l2.go = "OS_Matros_7_fortuna";
		break;
		
		case "OS_Matros_7_harizma":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddQuestRecord("OS", "3");
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Matros_7_fortuna":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddQuestRecord("OS", "3");
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Dialog_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "おい、ジャック！お前の部屋に港のあばずれがいるじゃねえか！ははっ！よく見てみろよ――なかなかの小悪魔だぜ！さて、あいつは俺たちの宝箱を全部漁ったのか、 それとも一番面白いところで俺たちが邪魔しちまったのか？";
				link.l1 = "...";
			}
			else
			{
				dialog.text = "おい、ジャック！見ろよ、こいつは盗みを働くネズミだぜ！ハハッ！この悪党を見てみろよ！ もう俺たちの海の宝箱を漁ってやがる、こそこそした野郎め！";
				link.l1 = "...";
			}
			link.l1.go = "OS_Dialog_2";
		break;

		case "OS_Dialog_2":
			StartInstantDialog("OS_Jack", "OS_Dialog_3", "Quest\\MiniEvents\\OldScores_dialog.c");
		break;

		case "OS_Dialog_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "大胆な小娘だな。ジャック・ヴェイルズの巣に乗り込むなんて、そんな度胸のある奴はそうはいねえ。\nで、何の用だい、お嬢ちゃん？俺たちを楽しませてくれるつもりか？";
				link.l1 = "楽しませろだと？はっ！お前ら、ずいぶん夢見がちな連中だな。俺は盗まれた物を取り返しに来たんだぜ。 あんなみみっちい芝居でごまかせると本気で思ったのか？";
			}
			else
			{
				dialog.text = "まったく大胆な虫けらだな。ジャック・ヴェイルズの家に忍び込むなんて、普通の奴じゃとてもやらねえぞ。さて、 ここで一体何の用だ？";
				link.l1 = "盗まれた品を取り戻しているだけさ。\nそれとも、あんたら紳士がやってるみみっちい茶番がバレないと本気で思ってたのか？";
			}
			link.l1.go = "OS_Dialog_4";
		break;

		case "OS_Dialog_4":
			StartInstantDialog("OS_capWolf", "OS_Dialog_5", "Quest\MiniEvents\OldScores_dialog.c");
		break;

		case "OS_Dialog_5":
			if (pchar.sex == "woman")
			{
				dialog.text = "みじめな出来だと！？悪魔に焼かれてもかまわねえ、てめえの皮をはいで帆にしてやるぜ！ハハハ！だが、 まずは少し遊ばせてもらうかもな？";
				link.l1 = "貴様ら、自分の死に急いでるようだな？よし、待たせねえぜ――かかってこい、この汚ねえ野郎ども！";
			}
			else
			{
				dialog.text = "みじめな茶番だと？悪魔にでもくれてやるぜ、てめえの皮をはいで帆布にしてやる！もう言葉はいらねえ――覚悟しろ、このクズ野郎！";
				link.l1 = "そう来るなら、かかってこい、この悪党ども！";
			}
			link.l1.go = "OS_Dialog_bitva";
		break;
		
		case "OS_Dialog_bitva":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("OS_Jack");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("OS_capWolf");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "OS_VernuliBochonok");
		break;
		
		case "Zaharia_1":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = ""+sld.name+"「俺のジンはどこだ！？もし持ってねえなら、この俺が直々にお前を港の底で魚のエサにしてやるぞ！」";
			link.l1 = "...";
			link.l1.go = "Zaharia_2";
			CharacterTurnByChr(npchar, sld);
			//locCameraFromToPos(-2.53, 2.00, 1.26, false, 0.03, 0.00, -1.11);
		break;

		case "Zaharia_2":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "...";
			link.l1 = "今しがた自分で届けたぜ。ほら、これだ。";
			link.l1.go = "Zaharia_3";
			CharacterTurnByChr(npchar, pchar);
			TakeItemFromCharacter(pchar, "cask_gin");
			notification("You gave the barrel of gin", "NONE");
		break;

		case "Zaharia_3":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "「俺がお前を信じたのは間違いじゃなかったようだな」 "+sld.name+"。明日俺の部屋に来い、ドブロン銀貨を渡してやる。";
			link.l1 = "...";
			link.l1.go = "Zaharia_4";
			CharacterTurnByChr(npchar, sld);
		break;
		
		case "Zaharia_4":
			DialogExit();
			
			//ChangeShowIntarface();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("OS_Zaharia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.lifeday = 0;
			sld.location = "None";
			
			DoQuestFunctionDelay("OS_RazgovorTavern", 1.5);
		break;
		
		case "Tavern_1":
			dialog.text = "船長、その銘板の件ですが……";
			link.l1 = "「何の銘板だ？ああ、それか……正直、そんな名誉はいらねえよ。俺のために気を遣うな。」";
			link.l1.go = "Tavern_2";
		break;

		case "Tavern_2":
			dialog.text = "もっと素晴らしいものを用意できるぜ！今日から、俺の酒場ではいつでも宿代も酒もタダだ！ あんたほどの人物なら当然の待遇だろうよ！";
			link.l1 = "そいつは俺の好みに合ってるぜ！こういう特権なら大歓迎だ！また会う日までな、 "+npchar.name+".";
			link.l1.go = "Tavern_3";
		break;
		
		case "Tavern_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			AddQuestRecord("OS", "5");
			AddQuestUserData("OS", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.OS_Tavern_FreeBuhlo = true;
			ChangeShowIntarface();
			
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			sld.dialog.filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First Time";
			LAi_SetBarmanType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			
			PChar.quest.OS_AttackSea.win_condition.l1 = "location";
			PChar.quest.OS_AttackSea.win_condition.l1.location = "Cuba1";
			PChar.quest.OS_AttackSea.function = "OS_AttackSea";
			
			// вражеский корабль атакует в море
			sld = CharacterFromID("OS_Pirate");
			DeleteAttribute(sld, "AlwaysFriend");
			DeleteAttribute(sld, "ShipEnemyDisable");
			sld.AlwaysEnemy = true;
			LAi_SetImmortal(sld, false);
			
			PChar.quest.TPZ_Potopil.win_condition.l1 = "NPC_Death";
			PChar.quest.TPZ_Potopil.win_condition.l1.character = "OS_Pirate";
			PChar.quest.TPZ_Potopil.function = "OS_Pobeda";
		break;
		
		
		
		
		
		
		
	}
}