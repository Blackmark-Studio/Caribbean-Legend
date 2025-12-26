// Санчо Карпентеро - бармен
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "出て行け！俺は通りで無実の人間を襲うクズどもには酒を出さねえぞ！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = ""+pchar.name+"！会えて本当に嬉しいぜ！俺は知ってた――知ってたんだ！――噂なんて嘘だってな！くそっ、一杯付き合ってくれよ！";
				link.l1 = "飲もうぜ、サンチョ！俺もお前に会えて本当に嬉しいぜ！";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			// пей до дна
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "fail")
			{
				dialog.text = ""+pchar.name+"申し訳ないな、負けちまったか。あのデブに酒で勝てる奴はほとんどいねえんだ。頭の具合はどうだ？";
				link.l1 = "お前……サンチョ、ずいぶん強いラムを出してくれるじゃねえか。酒のお代は……いくらだ？";
				link.l1.go = "drunk_fail";
				break;
			}
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
			{
				dialog.text = "「ファジオを倒したんだな。」 "+pchar.name+"！びっくりしたぜ！あいつに酒で勝ったやつなんて一人か二人しかいねえんだ。ほら、二百ドゥブロン受け取れよ。";
				link.l1 = "親切な言葉をありがとう、サンチョ！";
				link.l1.go = "drunk_win";
				break;
			}
			// крабовый салат
			if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "begin")
			{
				dialog.text = ""+pchar.name+"？お前、あのナーワルの技師が作った潜水服で海底まで潜ったって話を聞いたぜ。本当か？";
				link.l1 = "本当だぜ、相棒。俺は海の底を見たんだ！";
				link.l1.go = "crab";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "いらっしゃい！俺の酒場に新しい顔が来るのはいつだって嬉しいぜ！ようこそ！うちの酒場じゃ、 いつでもうまい酒が飲める――ヨーロッパのワインが船縁までぎっしりだ！\n食い物については……まあ、同じことは言えねえな。ははっ、冗談だよ。俺の名はサンチョ・カルペンテロ、ここは俺の店さ。";
				link.l1 = TimeGreeting()+"、サンチョ。俺の名は "+GetFullName(pchar)+"。はじめまして。";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "ああ、友よ "+pchar.name+"！会えて嬉しいぜ！どうするんだ？\n";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1" && !CheckAttribute(npchar, "quest.mushket"))
				{
					link.l6 = "聞いてくれ、サンチョ、どこかでいいライフルを手に入れられる場所を知らないか？普通の歩兵用マスケットじゃなくて、 もっと精度が高くて遠くまで届くやつだ――狩猟用とか、そんな感じの。";
					link.l6.go = "mushket";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_2")
				{
					link.l6 = "聞けよ、サンチョ、ちょっと聞きたいことがあるんだ。アドルフ・バルビエって男を探してるんだが、 よくここで飲んでるって聞いたんだが……";
					link.l6.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "barmen_whiskey")
				{
					link.l6 = "聞けよ、サンチョ、チャド・カッパーがあんたからヒ素を買ったって話だが……";
					link.l6.go = "whiskey";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.rat"))
				{
					link.l7 = "サンチョ、見せたいものがあるんだ。これはお前が手に入れようとしていたコウモリの仮面か？";
					link.l7.go = "rat";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.ratmoney") && PCharDublonsTotal() >= 1)
				{
					if (PCharDublonsTotal() >= sti(npchar.quest.ratmoney))
					{
						if(!CheckAttribute(npchar, "quest.ratmoneyagain")) ChangeCharacterComplexReputation(pchar, "fame", 5);
						link.l7 = "サンチョ、俺の胸当てを取りに来たぜ。ほら、金だ。";
						link.l7.go = "rat_3";
					}
					else
					{
						npchar.quest.ratmoneyagain = true;
						link.l7 = "サンチョ、俺は自分の胸当てを取りに来たんだ。ほら、金だ。";
						link.l7.go = "rat_take_money_not_all";
					}
				}
				if (makeint(pchar.money) >= 25)
				{
					link.l1 = "ラムを注いでくれ、サンチョ。";
					link.l1.go = "drink";
				}
				if (makeint(pchar.money) >= 20)
				{
					link.l2 = "部屋を借りたいんだ。";
					link.l2.go = "room";
				}
				if (stf(environment.time) >= 6.0 && stf(environment.time) <= 18.0 && makeint(pchar.money) >= 300)
				{
					link.l9 = "退屈だな、サンチョ。夕方になるまで、ここでワインでも飲みながら時間を潰したいよ……";
					link.l9.go = "drink_sit";
				}
				link.l3 = LinkRandPhrase("最近は何の話題が多いんだ、サンチョ？", "最近、この正義の島で何が起きているんだ？", "何か噂はあるか？");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "current" && CheckCharacterItem(pchar, "crab_pincers"))
				{
					link.l10 = "サンチョ、カニのハサミを売ってやるぜ。";
					link.l10.go = "crab_trade";
				}
				link.l4 = "サンチョ、島のことでちょっと聞きたいことがあるんだ。";
				link.l4.go = "int_quests"; //информационный блок
				link.l5 = "いや、相棒。ちょっと様子を見に来ただけだ。じゃあな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "俺もさ。せめて一晩に一度は顔を見せてくれるといいな、ははっ！俺の酒場に新しい客が来てくれて、本当に嬉しいぜ。";
			if (makeint(pchar.money) >= 25)
			{
				link.l1 = "ラムを注いでくれ、サンチョ。";
				link.l1.go = "drink";
			}
			if (makeint(pchar.money) >= 20)
			{
				link.l2 = "部屋を借りたいんだ。";
				link.l2.go = "room";
			}
			link.l3 = "サンチョ、島についてちょっと聞きたいことがあるんだ。";
			link.l3.go = "int_quests"; //информационный блок
			link.l4 = "じゃあな、サンチョ！";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mushket":
			dialog.text = "いや、旦那、俺には手伝えねえよ。俺の専門はビールとワインであって、マスケットじゃねえんだ、ははっ！ 店に行ってみな、アクセルが時々面白い武器を売ってるって聞いたぜ。そこで欲しいものが見つかるかもしれねえな。";
			link.l1 = "助言ありがとう。";
			link.l1.go = "exit";
			npchar.quest.mushket = "true";
		break;
		
		case "adolf":
			dialog.text = "アドルフ？ああ、時々ここに来るよ、でもここ数日は見かけていないんだ。あの太った男、 ジュゼッペと話してから行方がわからなくなってるんだよ。";
			link.l1 = "「ジュゼッペ…ジュゼッペ・ファツィオのことか？」";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "この島にジュゼッペは一人だけだ。ああ、そいつさ。何時間か一緒に座って、ラム酒を一本空けて、 ずいぶんと賑やかに語り合ってたぜ。";
			link.l1 = "奴らは言い争っていたのか？";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "いいや。あいつらは昔からの友人みたいに話してたぜ。なあ、カロライン号にいるファジオのところへ行って、 直接聞いてみな。";
			link.l1 = "わかった、そうするよ。";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			dialog.text = "それだけか？いくつか質問があるって言ってたじゃねえか…";
			link.l1 = "ああ。教えてくれ、レッド・メアリーとマルチェロ・サイクロプスって誰だ？";
			link.l1.go = "adolf_4";
		break;
		
		case "adolf_4":
			dialog.text = "レッド・メアリーはナーワル族の一人だ。若くて美しい娘だが、まったくもって野生児さ。 剣も拳銃も男顔負けの腕前だぜ。かつてはナーワル族の元リーダー、アラン・ミルローの恋人だったが、 提督にアランが殺されてしまったんだ\nアランの死は彼女にとって大きな打撃だった。今じゃセレス号の自分の船室で泣きながらシャークを呪ってばかりさ……だが、そのうち立ち直るだろう。人生は続くからな\nマルチェロについてはあまり知らねえ、何度か見かけただけだ。怖い奴だよ。昔は王室の狩人だったらしいが、 戦いで片目を失い、傭兵として商船に乗り込んだ――敵の乗り込みを撃退して海で日々を過ごしてたそうだ\nまあ、当然だが……奴は海賊が大嫌いさ";
			link.l1 = "そうか……ありがとう、Sancho、君は本当に助かったよ。";
			link.l1.go = "adolf_5";
		break;
		
		case "adolf_5":
			dialog.text = "どういたしまして、相棒。また会いに来いよ、一緒にエールでも飲もうぜ。";
			link.l1 = "もちろんだぜ！";
			link.l1.go = "adolf_6";
		break;
		
		case "adolf_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_3"; //флаг на Джузеппе
			AddQuestRecord("SharkHunt", "13");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "カッパー？いや、最近は酒場に来てないな。マルチェロ・サイクロプスがたった今、 十五分前にヒ素の小瓶を買っていった――あいつもネズミに悩まされてるんだろうな。気持ちはよく分かるぜ……くそったれなネズミどもめ。";
			link.l1 = "サイクロプスがここにいたのか！？";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "ああ、そうだが。どうしてだ？";
			link.l1 = "ここ数日ずっと彼を探しているんだ。どこへ行ったか知ってるか？";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "彼はサンタ・フロレンティナに住んでいるアドルフ・バルビエと一緒だった。もしかすると、 そこへ向かったのかもしれないな？";
			link.l1 = "ありがとう！";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "ヒ素が必要なら、小瓶一つ二十ドゥブロンで売ってやるぜ――！";
			link.l1 = "その話は後だ、サンチョ、じゃあな！";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "whiskey_poison"; // флаг - виски травят
			AddQuestRecord("SharkHunt", "37");
			sld = CharacterFromID("LSC_Adolf");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "whiskey"; // ноду Акуле
			// важный момент! От дальнейшего поведения геймера зависит результат
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1.location = "SantaFlorentinaShipInside4";
			pchar.quest.LSC_Whiskeypoison_SF.function = "LSC_WhiskeyPoison_SF"; // прерывание на Санта-Флорентину
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_Whiskeypoison_AE.function = "LSC_WhiskeyPoison_AE"; // прерывание на Эву
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Whiskeypoison_exit.function = "LSC_Whiskeypoison_exit"; // прерывание на выход из таверны
			// закрываем вход к Фацио
			LocatorReloadEnterDisable("LostShipsCity_town", "reload20", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload24", true);
		break;
		
		// пей до дна
		case "drunk_fail":
			dialog.text = "さあ、相棒、俺に借りなんてねえよ。もう百ドゥブロンも失ったじゃねえか。ファジオと飲み比べしようなんて思うから、 そうなるんだよ……";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "いや、いや、サンチョ、頼む！この五百ペソを受け取ってくれ。俺の記憶が正しければ、それで酒代は足りるはずだ。 君に借りを作りたくないんだ。";
				AddMoneyToCharacter(pchar, -500);
			}
			else link.l1 = "ええ…ありがとう、サンチョ。君の言う通りだ。";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		case "drunk_win":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You have received 200 doubloons");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		// крабовый салат
		case "crab":
			dialog.text = "ふむ……それなら提案があるんだ。下の方で巨大なカニを見かけなかったか？";
			link.l1 = "冗談じゃねえよ！奴らは大勢いたんだぜ！お前は何を考えてたんだ？";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "もし奴らを殺したら、必ずその爪を俺のところに持ってきてくれ。ドブロン銀貨でしっかり払うぜ――一つにつき五枚だ！アクセル・ヨストじゃ、そんなに払いやしねえ、保証するぜ。\n狩りに行けとは言わねえが……もし一匹か二匹仕留めたら、俺の話を思い出してくれよ……";
			link.l1 = "なぜハサミなんだ？カニの他の部分はどうしたんだ？";
			link.l1.go = "crab_2";
		break;
		
		case "crab_2":
			dialog.text = "ほとんどの身はハサミにあるからさ。カニの脚にはあまり身がなくて、胴体は硬い殻に覆われてるんだ。 カニの身はこの島じゃごちそうだぜ。味は絶品だし、栄養もたっぷりなんだ！\n俺だけの特別なレシピがあるから、ハサミ一つにつき五ドゥブロンで買い取るぜ。";
			link.l1 = "わかった、覚えておくよ……";
			link.l1.go = "crab_3";
		break;
		
		case "crab_3":
			DialogExit();
			npchar.quest.crab = "current";
		break;
		
		case "crab_trade":
			iTotalTemp = GetCharacterItem(pchar, "crab_pincers")
			dialog.text = "素晴らしい！いくつ持っているんだ？";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			link.l1.go = "crab_trade_1";
			link.l2 = "気が変わった。";
			link.l2.go = "exit";
		break;
		
		case "crab_trade_1":
			dialog.text = "よし。ほら、ドゥブロン金貨を受け取れ― "+FindRussianQtyString(iTotalTemp*5)+"。ありがとな、相棒。もっと手に入れたら、俺のところに持ってきてくれよ。";
			link.l1 = "「ああ、友よ。」";
			link.l1.go = "crab_trade_2";
		break;
		
		case "crab_trade_2":
			DialogExit();
			RemoveItems(pchar, "crab_pincers", iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+iTotalTemp*5+" doubloons");
		break;
		
		// крыс
		case "rat":
			dialog.text = "「何だって！？見せろ！俺にも見せてくれ！」";
			link.l1 = "わかった、わかった、ははは！";
			link.l1.go = "rat_1";
		break;
		
		case "rat_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "こ、これだ！水夫が描いてくれた絵とまったく同じだ！\n友よ……これを俺に売ってくれないか？";
			link.l1 = "それは場合によるな。俺の記憶じゃ、この品に王様の身代金並みの報酬を約束したはずだぜ。";
			link.l1.go = "rat_2";
			link.l2 = "悪いな、相棒、これは売り物じゃねえんだ。俺の船に必要だからな。ただ、本当にお前が言ってた護符かどうか、 確認してほしかっただけさ。";
			link.l2.go = "rat_exit";
		break;
		
		case "rat_exit":
			PlaySound("interface\important_item.wav");
			dialog.text = "ああ、残念だな……そうだよ、友よ、これがあの護符さ。運のいい奴め！これでもう二度とネズミに悩まされることはないぜ！ 俺はこれからもヒ素で駆除し続けなきゃならねえがな……";
			link.l1 = "期待させてしまって悪かったな、サンチョ。俺もこの品がどんなものか分からなかったから、確かめる必要があったんだ。 すまねえ。";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.rat");
		break;
		
		case "rat_2":
			dialog.text = "これのために、"+pchar.name+"……俺が……俺が持ってる中で一番素晴らしくて貴重な品を買うチャンスをやろう！今、持ってくるからな……\n見てくれ。これが唯一無二、輝かしいミラノ製キュイラスだ。名匠の手による逸品だぜ！ 戦闘時には抜群の防御力を発揮し、動きも妨げず、しかも軽くて着心地もいい。こんな上等な鎧は、 カリブでもヨーロッパでも滅多にお目にかかれねえぞ。\n数年前、スペインの戦列艦の艦長室で偶然見つけてな、こんな機会のためにずっと取っておいたんだ。 二千枚の金貨とラット・ゴッドを出してくれるなら、あんたに売ってやるぜ！";
			link.l1 = "ふむ……これは、なんと見事なキュイラスだ！この取引、俺には悪くねえな。ネズミの始末の仕方はいくらでもあるが、 こんなキュイラスをもう一度手に入れるのはほとんど不可能だろう。こんなの、今まで見たことがねえ。 本当に唯一無二の鎧だぜ。";
			link.l1.go = "rat_yes";
			link.l2 = "「なんだと！？サンチョ、お前のネズミども、今朝すでに何度かお前を噛んだんじゃねえのか？二千だと？ その意味が分かってるのか？この偶像を見つけるのにどれだけ苦労したと思ってるんだ！？今すぐ値段を下げろ！」";
			link.l2.go = "rat_torg";
			link.l3 = "なんだと！？お前はサメかよ、サンチョ？「買う機会を提供する」だと―はっ！その金額があれば、本土で弾丸をはじいて水の上を歩ける鎧を自分用に注文できるぜ！それに、 そんなに大量の金が何に必要なんだ？ユルゲンに自分の像でも作らせて、サン・アグスティン号の甲板に飾るつもりか？";
			link.l3.go = "rat_no";
		break;
		
		case "rat_yes":
			dialog.text = "乗ってくれて嬉しいぜ、相棒。俺の問題を忘れずにいてくれて感謝する！だから、ドブロン金貨を期待してるぜ。 鎧は用意して待ってるからな！";
			link.l1 = "すぐに連れてくるぜ！";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 2000;
		break;
		
		case "rat_torg":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				Notification_Skill(false, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+"状況が違えば、俺は五千を要求していただろう。提督ご自身も興味を示している――しかも、彼だけじゃないんだ、信じてくれ。だが、ゆっくり考えてくれていい。鎧は必要なだけ待たせておくさ。 お前にしか売らないからな。";
				link.l1 = "考えておくよ、サンチョ。";
				link.l1.go = "rat_yes_1";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+"状況が違えば、俺は五千要求してたぜ。提督ご自身も興味を示してる――しかも、彼だけじゃねえんだ、信じてくれ。\nまあいい、五百まけてやるよ。お前が俺と俺の問題を忘れなかったことを考慮してな。大変な冒険だったに違いねえ。";
				link.l1 = "それで少しはマシになったが……それでも、同じくらい珍しい品同士の取引で、なぜ俺が余分に払わなきゃならねえんだ？ むしろお前が俺に払うべきじゃねえか、なあサンチョ、へへっ？";
				link.l1.go = "rat_yes_1500";
				AddCharacterExpToSkill(pchar, "Commerce", 100);
			}
		break;
		
		case "rat_yes_1500":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 90)
			{
				Notification_Skill(false, 90, SKILL_COMMERCE);
				dialog.text = "いいや "+pchar.name+"…無理だな。ネズミならヒ素でどうにかできるが、この鎧はいつかお前の命を救うかもしれねえんだぜ。それに、 これを着ればイタリアの公爵みてえに見えるぞ！千五百だ、それが俺の最終提示だ。ゆっくり考えてくれていい、 決まったら教えてくれ。この鎧はお前のためにいつまでも取っておく、他の誰にも売らねえよ。";
				link.l1 = "サンチョ、この陰気な墓場でお前が唯一の酒場の主人じゃなけりゃな……お前の申し出、考えておくよ。";
				link.l1.go = "rat_yes_1500exit";
				AddCharacterExpToSkill(pchar, "Commerce", 600);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = "軍人の船長でありながら海賊でもあるくせに、交渉術はなかなかのもんだな！ヨーストを覚えてるか？あいつなんて、 ネズミに苦しめられてる最中に俺のヒ素を全部まとめて値引きで買い取ったことがあるんだぜ。\nよし、 "+pchar.name+"、あんたの勝ちだ。さらに五百引いてやるよ！でも、これが最後の値引きだぜ！";
				link.l1 = "まだぼったくられてる気がするけど、少なくともこれでジャングルでよくいる困ったお姫様みたいな気分にはならないわ。 \n待ってて、すぐにお金を持ってくるから。";
				link.l1.go = "rat_yes_1000exit";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
		break;
		
		case "rat_no":
			dialog.text = "「落ち着け」 "+pchar.name+"。他の誰かなら、五千も要求するところだぜ！提督ご自身も興味を示している――しかも、信じてくれ、彼だけじゃねえんだ。\n鎧はお前のために取っておく。他の奴にはその間、絶対に売らねえよ。";
			link.l1 = "なんて光栄だ！すぐ戻るぜ。二千だ！";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1500exit":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1500;
		break;
		
		case "rat_yes_1000exit":
			Achievment_SetStat(106, 1);
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1000;
		break;
		case "rat_3":
			dialog.text = "終わったな！同意してくれて嬉しいぜ、相棒。俺の問題を忘れずにいてくれて感謝する！この胸当てを持っていけ、 戦で役立ててくれよ。";
			link.l1 = "ほら、お守りを持っていけ――お前の酒場にいるネズミどもには暗い時代が来そうだな、ははっ！";
			link.l1.go = "rat_4";
		break;
		
		case "rat_4":
			DialogExit();
			GiveItem2Character(pchar, "cirass4");
			RemoveItems(pchar, "talisman1", 1);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.ratmoney));
			Log_Info("You have given away the talisman 'God of rats'");
			Log_Info("You have received a Milanese armor");
			Log_Info("You gave "+FindRussianDublonString(sti(npchar.quest.ratmoney))+"");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.ratmoney");
			if(CheckAttribute(npchar, "quest.ratmoneyagain"))
				DeleteAttribute(npchar, "quest.ratmoneyagain");
		break;
		
		case "rat_take_money_not_all":
			npchar.quest.ratmoney = sti(npchar.quest.ratmoney) - PCharDublonsTotal();
			Log_Info("You gave "+FindRussianDublonString(PCharDublonsTotal())+"");
			RemoveDublonsFromPCharTotal(PCharDublonsTotal());
			PlaySound("interface\important_item.wav");
			dialog.text = "今でも俺を圧倒させるぜ "+FindRussianDublonString(sti(npchar.quest.ratmoney))+", "+pchar.name+".";
			link.l1 = "「思い出させるな！」";
			link.l1.go = "exit";
		break;
		
		//--> информационный блок
		case "int_quests":
			dialog.text = "聞いてるぜ、友よ。";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "ここは何という島なんだ？もっと詳しく教えてくれないか？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "「どうやってこの正義の島を出ればいいんだ？」";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "この島について何を知っておくべきだ？";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "ここでの暮らしはどうだい？酒場の調子はどうなんだ？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない、気にしないでくれ……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "この島かい？まあ、正義の島とか、正義の島とか、捨てられた船の街なんて呼ばれてるが、俺たちはただ「島」 って呼んでるよ。ここは難破船が集まってできた島で、全部が礁の真ん中の浅瀬に引っかかってるんだ。\nこの島の中心部が俺たちの住む場所で、外側の難破船の輪は誰も住んでない。外の世界とはもう十年も繋がりがないんだ。 ";
			link.l1 = "信じられねえ！";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "長艇や筏を作っても、うまくはいかねえよ。嵐と強い潮流がこの島を囲んでいて、外輪を越えたら命がけだぜ。\n生き残るには一流の船乗りのチームが必要だが、この島を出たがる奴はほとんどいねえ。 ましてや外輪の外に出る危険を冒す奴なんて、さらに少ねえさ。\nここでの暮らしを気に入ってる連中が多いんだ。信じられねえなら、周りに聞いてみな。";
			link.l1 = "なるほど……";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "まず最初に、この島にはいくつか立ち入り禁止区域があることを覚えておくべきだ。 ナーワルとリバドスという二つの氏族が長い間ここに住み着き、互いに絶え間なく争い、 それぞれが自分たちの領土だと考える場所を守っている。招かれずに彼らの元を訪ねれば、命はないぞ。\n彼らの領域に入るには、今の合言葉を知っていなければならない。うっかり侵入してしまっても心配はいらない、 見張りが何度か警告してから撃ってくるからな。";
			link.l1 = "覚えておくよ……";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "あのな、旦那、別にいいんだよ。俺は食い物と酒の世話には慣れてる。ヨーロッパじゃあちこちで料理人やってきた――駐屯地、酒場、船の上――だからここに来て最初にやったのが酒場を開くことだったんだ。\nこの仕事が好きだし、今の暮らしにも満足してる。誰だって食い物と酒は必要だし、俺はそれを出すのが楽しいんだ。 ここじゃみんな気さくで、たいてい穏やかだ。酔っぱらいの喧嘩の後片付けをしたのがいつだったか、 もう思い出せねえよ。部族連中も俺にはちょっかい出さねえしな。\n結局のところ、ここが俺の人生で一番いい場所だ。ここじゃ自由だし、誰にも指図されねえ。\nただ一つだけ頭にくるのはネズミどもだ。あいつらは俺を苦しめやがる――食料を食い荒らし、食器を台無しにしやがる。どうやっても追い払えねえんだよ。";
			link.l1 = "ああ、あのガキどもがどれだけ厄介か、俺は身をもって知ってるぜ…";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "どうやらこの街でネズミに関して一番不運なのは俺みたいだ。 他の船はうちのフルーロンほどひどくネズミに悩まされちゃいねえ。 アクセル・ヨーストはどうにかして一度でネズミを全部追い払ったらしいが、 俺のところは今も毛むくじゃらの野郎どもが大軍で這い回ってるんだ。\nそういえば、昔「ネズミの神」っていう特別な護符の話を聞いたことがある。コウモリの顔みたいな形をしてるらしい。 その護符があれば、ネズミが完全に逃げ出すってさ。\nきっとアクセルもそれでネズミを追い払ったんだろうよ。 あいつは外輪から持ち込まれるガラクタを全部買い取っては売りさばいてるからな。\nもし誰かがその護符を持ってきてくれたら、王様の身代金を払ってでも手に入れたいぜ！";
			link.l1 = "覚えておくぜ……";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
			npchar.quest.rat = "true";
		break;
		//<-- информационный блок
		
		//--> выпивка
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 4)
			{
				dialog.text = ""+pchar.name+"もう十分だと思うぜ、相棒。神様が守ってくれるとは限らねえし、強盗に遭ったり、 海に落ちてカニの餌になるかもしれねえ。ここで酒を飲みすぎるのは命取りだ、気をつけな。";
				link.l1 = "ふむ……確かにその通りだな、サンチョ。ひっく……もう十分飲んだよ。心配してくれてありがとな。";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -25);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "どういたしまして、相棒。俺の最高のラム酒一杯でたったの二十五ペソだぜ！";
				link.l1 = RandPhraseSimple(LinkRandPhrase("お前の健康と酒場の繁盛に乾杯だ、相棒！","海の民すべてに、どこにいようとも！","正義の島の皆さんへ！"), LinkRandPhrase("正義の島に、そして永遠に続きますように！","どんな航路を取ろうとも、いつも順風が吹きますように！","運と幸せ……そして女たちに乾杯だ！"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
		break;
		
		case "drink_sit":
			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "今は酒を飲むべきじゃねえと思うぜ。俺を信じろ……";
				link.l1 = "……わかった……";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				dialog.text = "へっ、あんたも変わった奴だな……この島で暇をつぶす相手はいねえのか？ここで一人で飲ませたら、メアリーに殺されちまうぜ。 夕方になったら誰かと一緒に来て、夜明けまで好きなだけ楽しんでくれよ。";
				link.l1 = "いい考えだな！";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "問題ねえよ、相棒。たった三百ペソで上等な一本を手に入れられるぜ "+LinkRandPhrase("Spanish","Italian","French")+" ワイン――そして好きなだけ使える席だよ。";
				link.l1 = "ありがとう！";
				link.l1.go = "drink_sit_1";
			}
		break;
		
		case "drink_sit_1":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_DrinkSit");
		break;
		//<-- выпивка
		
		//--> сон в таверне
		case "room":
   			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "今は寝ないほうがいいと思うぜ。俺を信じろ……";
				link.l1 = "「いいだろう。」";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				if(!isDay())
				{
					dialog.text = "お前の言ってることがわからねえな、相棒。セレス号にはお前を待ってる美人がいるってのに、 一人で酒場で夜を過ごすつもりか？そんなの許せねえよ、メアリーに殺されちまうからな。";
					link.l1 = "たぶん、君の言う通りだな……";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "夕方までなら二階で休んでいいが、夜はここに泊められねえ。メアリーに殺されちまうからな。悪いな……";
					link.l1 = "仕方ねえ、夕方までここにいるとするか……";
					link.l1.go = "hall_night_wait";
					link.l2 = "……仕方ねえ……寝なくてもなんとかするさ。";
					link.l2.go = "exit";
				}
				break;
			}
			dialog.text = "20ペソで、二階のベッドで寝られるぜ。いつ起こせばいいんだ？";
			if(!isDay())
			{
				link.l1 = "朝に。";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "日が暮れる前に。";
				link.l1.go = "hall_night_wait";
				link.l2 = "翌朝。";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "気が変わった。眠りたくない。";
			link.l3.go = "exit";
		break;
		
		case "hall_night_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		
		case "hall_day_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//<-- сон в таверне
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
