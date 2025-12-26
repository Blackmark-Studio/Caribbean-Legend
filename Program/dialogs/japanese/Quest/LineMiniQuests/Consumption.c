// диалоги по квесту Цена чахотки
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Consumption == "final")
			{
				dialog.text = "船長！海に出たって聞いたぜ！どうだったんだ？何か分かったのか？頼む、教えてくれよ、早く話せ！";
				if (CheckAttribute(pchar, "questTemp.Consumption.TakeMoney"))
				{//взял деньги
					link.l1 = "いや、俺の美人さんよ、この襲撃は閣下である総督の依頼で行われたんだ。すまねえが、 アンジェロは砦の地下牢で死んじまった――今となっては疑いようがねえ。しっかりしろよ！ ";
					link.l1.go = "Waitress";
				}
				else
				{//убил Хуана
					if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
					{
						link.l1 = "あんたの言った通りだったぜ。あんたの兄貴は誘拐されてたんだ。司令官は囚人たちを家畜みたいに「消耗品」 ってあだ名の奴隷商人に売り飛ばしてた。でも俺がその船を追い詰めて、今じゃあいつは海の底さ。 あんたの兄貴アンジェロももうすぐ上陸できるだろう。残念だが、 全員を一度に岸へ運ぶだけのロングボートは持ってねえんだ。 ";
						link.l1.go = "Waitress_2";
					}
					else
					{//отпустил Хуана
						link.l1 = "お前の言った通りだった。お前の兄弟は誘拐されていたんだ。司令官は囚人たちを家畜のように「コンスンプション」 と呼ばれる奴隷商人に売っていた。だが、俺はそいつの船に追いついた。あの野郎を仕留めることはできなかったが、 お前の兄弟アンジェロはもうすぐ上陸できるはずだ。残念ながら、 一度に全員の乗客を岸に運ぶだけのロングボートが足りないんだ。\n ";
						link.l1.go = "Waitress_2";
					}
					sld = characterFromId("ConAndjelo");
					sld.lifeday = 0;
					RemovePassenger(Pchar, sld);
				}
			}
			else
			{
				dialog.text = "アンジェロの運命について何かわかったか、船長？";
				link.l1 = "まだだ。だが、すぐに知らせが入ると思うぜ。少し待っていればいいさ。 ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "without_moneysss": // лесник  если Гг нажрался..сволочь:D:D:D
		    dialog.text = "旦那、兄を探してくれるって約束したじゃないか……なんでここで酒なんか飲んで時間を無駄にしてるんだ？";
			link.l1 = "おお…ああ、そうだな…ひっく…落ち着け、お嬢ちゃん…イエス様が見てるからな…ずずっ…イエス様が見てるんだ。俺はもうダメだ…ひっく…";
			link.l1.go = "exit";
		break;
		
		case "Servant":
			dialog.text = "こんにちは、旦那。ここで何の用だ？";
			link.l1 = "俺は旦那コマンダンテへの伝令を持ってきたが、本人に直接渡したほうがいいんだ。";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "それなら、砦でそいつを探してこい。";
			link.l1 = "この伝令はとても重要で、兵士どもの目や耳に入れてはならねえ。俺が早く来すぎたかもしれねえが、 ここであいつを待つさ。信じてくれ、これは本当に大事なんだ！";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < 40)
			{
				notification("Skill Check Failed (40)", SKILL_SNEAK);
				dialog.text = "旦那コマンダントは、普段から日課を変えなきゃならない大事なことがあれば必ず俺に知らせてくれるんだ……実はな、この件についてもちゃんと警告してくれてたんだよ。";
				link.l1 = "「それで、あいつは何て言ったんだ？」";
				link.l1.go = "Servant_3";
			}
			else
			{
				notification("Skill Check Passed", SKILL_SNEAK);
				dialog.text = "よし、信じてやるよ。だがな、旦那コマンダンテが来てお前の言葉を確かめるまでは、もっと信じることはできねえ。\nそれまではずっとお前を見張ってるからな。";
				link.l1 = "好きなだけ俺のことを見てていいぜ……";
				link.l1.go = "Servant_4";
			}
		break;
		
		case "Servant_3":
			dialog.text = "こういう時は守備隊の兵士を呼べって言われたが、まあ、俺たちだけで何とかなるだろう。\n野郎ども！こいつをぶっ殺せ！";
			link.l1 = "くそっ！";
			link.l1.go = "Servant_fight";
		break;
		
		case "Servant_4":
			DialogExit();
			NextDiag.CurrentNode = "Servant_repeat";
			LAi_SetOwnerType(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Servant_repeat":
			dialog.text = "他に何が欲しいんだ？伝言を渡す気になったのか？";
			link.l1 = "いや、俺は司令官を待つぜ……";
			link.l1.go = "exit";
			NextDiag.TempNode = "Servant_repeat";
		break;
		
		case "Servant_fight":
			int iRank = sti(pchar.rank)+5;
			int iScl = 15 + 2*sti(pchar.rank);
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true;
			for (i=9; i<=11; i++)
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Conservant_"+i, "citiz_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto5");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Consumption_AfterHouseFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//попытка залезть в сундук
		case "Man_FackYou":
			dialog.text = "お前は泥棒か！？それともスパイか？野郎ども、下の階だ、急げ！";
			link.l1 = "がっ、くそっ！";
			link.l1.go = "Servant_fight";
		break;
		
		case "Sergio":
			dialog.text = "失礼します、お話ししてもよろしいですか？";
			link.l1 = "正直言って、俺は急いでるんだ。何の用だ？";
			link.l1.go = "Sergio_1";
		break;
		
		case "Sergio_1":
			dialog.text = "俺は聞いちまったぜ、あんたがフアンって男と、うちの牢屋で流行ってる病気について聞き回ってるってな……";
			link.l1 = "確かにそうだ……説明してくれないか？";
			link.l1.go = "Sergio_2";
		break;
		
		case "Sergio_2":
			dialog.text = "落ち着け、落ち着け！剣に手を出すな！俺たちは味方同士だぜ！あんたが俺たちの問題に興味を持つ理由は知らねえが、 これは止めなきゃならねえ！もうこれ以上黙っていられねえんだ！";
			link.l1 = "黙ってろ？何についてだ？お前は肺病について何を知ってるんだ？";
			link.l1.go = "Sergio_3";
		break;
		
		case "Sergio_3":
			dialog.text = "俺は色々知ってる、いや、ほとんど全部知ってると言ってもいい。だが、ここじゃ話せねえ。 夜になって明かりが消えたら会おう。俺は医療助手だから砦を出ることが許されてるんだ。町の門の外で会おう、 そこで全部話す。頼む、これ以上質問するな、やつらの注意を引く前に……いや、もう引いてるかもしれねえが……。もう行かなきゃならねえ。忘れるなよ、夜になったら町の門の外だ。";
			link.l1 = "わかった、行くぜ。おい！待てよ……";
			link.l1.go = "Sergio_4";
		break;
		
		case "Sergio_4":
			DialogExit();
			AddQuestRecord("Consumption", "8");
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption3.win_condition.l1 = "location";
			pchar.quest.Consumption3.win_condition.l1.location = "PortSpein_Exittown";
			pchar.quest.Consumption3.win_condition.l2 = "Hour";
			pchar.quest.Consumption3.win_condition.l2.start.hour = 0;
			pchar.quest.Consumption3.win_condition.l2.finish.hour = 3;
			pchar.quest.Consumption3.function = "Consumption_MeetSergio";
			pchar.quest.Consumption4.win_condition.l1 = "Timer";
			pchar.quest.Consumption4.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Consumption4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Consumption4.function = "Consumption_FailSergio";
			locations[FindLocation("PortSpein_Exittown")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("PortSpein_Exittown", true);//офицеров не пускать
		break;
		
		case "Sergio_5":
			dialog.text = "神に感謝する、来てくれたんだな……誰にも尾けられていないだろうな？";
			link.l1 = "なぜだ？お前は疑り深すぎるぜ、もしかすると旦那コマンダンテよりもな。だからさっさと本題に入ったほうがいい……フアンについて何か知ってるのか？";
			link.l1.go = "Sergio_6";
		break;
		
		case "Sergio_6":
			dialog.text = "俺の名はセルジオ・サルドだ。砦で医療助手をやっていてな……";
			link.l1 = "";
			link.l1.go = "Sergio_6_1";
		break;
		
		case "Sergio_6_1":
			dialog.text = "";
			link.l1 = "待て！今の音、聞こえたか？";
			link.l1.go = "Sergio_7";
			Play3DSound("lomanie_vetki", -33.25, 1.00, 3.73)
		break;
		
		case "Sergio_7":
			dialog.text = "「何だって！？どこだ？」";
			link.l1 = "くそっ、ここには俺たちだけじゃねえ……おい、てめえ、誰を連れてきやがったんだ、このクズ野郎？";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Consumption_CreateBandits");
		break;
		
		case "Bandit":
			dialog.text = "見つかったぞ！お前は医者を頼む、俺はもう一人をやる！";
			link.l1 = "...";
			link.l1.go = "Bandit_1";
		break;
		
		case "Bandit_1":
			DialogExit();
			sld = characterFromId("Sergio");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=3; i++)
			{	
				sld = characterFromId("Conbandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Conbandit_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Sergio_8":
			dialog.text = "剣を収めろ、もう終わりだ！お前も見ただろ、奴らは俺を殺そうとしたんだ！";
			link.l1 = "ふむ、不正を働くにはあまりにも手が込んでいるようだな――つまり、お前は奴らの仲間じゃねえってことか。\nどこまで話したっけ？お前は牢屋の医者なんだろう？";
			link.l1.go = "Sergio_9";
		break;
		
		case "Sergio_9":
			dialog.text = "ああ、そうだ。俺はこの牢獄の医者をやってる。若い頃に医学を学んだし、ここには学のある奴はあまりいねえからな。 だからこそ、牢獄で何が起きてるかは誰よりもよく知ってるんだ！";
			link.l1 = "どうなってるんだ？囚人たちはどうした？やつらが突然消えたことについて何か知ってるのか？";
			link.l1.go = "Sergio_10";
		break;
		
		case "Sergio_10":
			dialog.text = "うちの司令官は奴らを売ってるんだ……家畜みたいに、フアンっていう奴隷商人に売り飛ばしてる。誰にも気にされない連中を選ぶんだよ――貧乏人とか、どこかの船の水夫とかさ。それで、そいつらは急に「肺病で死んだ」ことになる……あとは察してくれよ……";
			link.l1 = "結局のところ、あのフアンも人間なんだな！お前は奴について何か知ってるのか？";
			link.l1.go = "Sergio_11";
		break;
		
		case "Sergio_11":
			dialog.text = "少しな。あいつは昔、ベルベル海賊と一緒にモロッコで汚い仕事をやってたんだ。たまにここに来ると、 その頃の話をよく語りたがるぜ。あそこで「コンスンプション」ってあだ名を手に入れたんだが……その由来は考えたくもねえな\n毎月ここに来て、囚人を全部自分の船に乗せていくんだ。";
			link.l1 = "「結核だと！？俺が皮肉屋だって言われたが、そういうことか……あんたの旦那指揮官は本当にクソ野郎だな！」";
			link.l1.go = "Sergio_12";
		break;
		
		case "Sergio_12":
			dialog.text = "俺の理解じゃ、あんたは行方不明の囚人の中の誰かを探してるんだろ？じゃなきゃ、こんな話を知るはずがねえよな、 違うか？そうなら、急いだほうがいいぜ。今夜が今月最後の夜だ。俺はすでにあと三人の死亡書類に署名したし、 フアンは明日の昼前にはそいつらを受け取って錨を上げるぞ！";
			link.l1 = "何に署名したんだ？俺にはよくわからねえんだが……";
			link.l1.go = "Sergio_13";
		break;
		
		case "Sergio_13":
			dialog.text = "俺はやらざるを得なかったんだ――もう何ヶ月も前からずっとそうしてきたんだぜ！だからこそ、これを止めるためにここへ来たんだ。\nドクトル・ピネロがどうやって死んだか知ってるか？俺の前に囚人たちを診ていたあの医者のことだ。";
			link.l1 = "確か彼は肺病で亡くなったと聞いたはずだが、違うのか？つまり、お前はやむを得ず巻き込まれたってわけだな。 それは筋が通ってる――だが、なぜ誰もこの件を当局に知らせなかったんだ？";
			link.l1.go = "Sergio_14";
		break;
		
		case "Sergio_14":
			dialog.text = "「こんな話、誰が信じるってんだ？証拠なんて持っちゃいねえし、 本来囚人を見張るはずの兵隊どももたっぷり金をもらってるから、 たとえカリブ人に囚人を食い物として売ってたって気にしやしねえ\n囚人なんざ誰も気にしちゃいねえ、それが司令官の切り札ってわけだ。だがな、あんたがフアンを始末すりゃ、 少なくとも当分の間はこの悪事を止められるぜ！」";
			link.l1 = "俺の理解だと、陸にいたあの連中はあいつの手下だったんだろ？どうやってそいつを見つけりゃいいんだ？";
			link.l1.go = "Sergio_15";
		break;
		
		case "Sergio_15":
			dialog.text = "お前の質問で誰かの注意を引いちまったかもしれねえな……もっと気をつけろって言っただろうが！だが今はそれどころじゃねえ。フアンの船については何も知らねえが、 囚人はいつも島の北部にあるガレラ岬へ送られるんだ。たぶん奴隷商人の船もその近くにいるはずだから、 追いつけるかもしれねえぞ。今日、奴の使いが「明日の正午に出航する」と言っていたぜ。\n";
			if (!CheckCharacterItem(pchar, "letter_consumption"))
			{
				link.l1 = "ありがとう、セルジオ、君は本物の士官であり、名誉ある男だ。今すぐ錨を上げて、この汚らしい船を見つけてやる。 君は捜索が始まる前に砦へ戻ったほうがいいぞ。";
				link.l1.go = "Sergio_16";
			}
			else
			{
				link.l1 = "さて、知りたいことはこれで全部だ。今すぐ錨を上げねえと、「コンスンプション」を新世界中探す羽目になるからな。\nその間に、これでも調べておけ。";
				link.l1.go = "Sergio_17";
			}
		break;
		
		case "Sergio_16":
			dialog.text = "幸運を祈るぜ、船長！俺のことは気にするな――一番大事なのは、これを少しでも止めることだ。健闘を祈ってるぜ！";
			link.l1 = "俺の大砲は病と悪を治す最良の薬だぜ。囚人どもは夜明け前に全員陸に上げてやると誓う――それにフアンの船は海の底で眠ることになる！";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_17":
			RemoveItems(PChar, "letter_consumption", 1);
			Log_Info("You have given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "何だと？ここに大佐の名前とモノグラム「J」があるじゃねえか？信じられねえ！どこでこれを手に入れたんだ？";
			link.l1 = "それは知らない方がいいが、きっとお前ならうまく活用してくれると信じてるぜ。";
			link.l1.go = "Sergio_18";
		break;
		
		case "Sergio_18":
			dialog.text = "やるさ、聖なるものすべてに誓って！大佐は今月が終わる前に絞首台行きだ！俺が自分の手で必ずやってやる！";
			link.l1 = "残念ながら、これは懲戒処分で終わるだろうな。しかも、あいつの人生で初めてじゃなさそうだぜ。いっそ、 あの野郎を撃ち殺した方がいいんじゃねえか？それが一番効く薬だ……さて、俺はもう行くぜ――「コンスンプション」を待たせたくねえからな。";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_19":
			DialogExit();
			AddQuestRecord("Consumption", "11");
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption5.win_condition.l1 = "location";
			pchar.quest.Consumption5.win_condition.l1.location = "Trinidad";
			pchar.quest.Consumption5.function = "Consumption_CreateJuan";
			pchar.quest.Consumption6.win_condition.l1 = "HardHour";
			pchar.quest.Consumption6.win_condition.l1.hour = 13;
			pchar.quest.Consumption6.function = "Consumption_FailJuan";
			// Сержио теперь наш друг и будет торговать смолами
			SetFunctionTimerCondition("Oil_PrepareSergio", 0, 0, 20, false); // таймер
		break;
		
		// генератор торговли смолами
		case "Sergio_20":
			dialog.text = "おお、なんて幸運な出会いだ！旦那 "+GetFullName(pchar)+"！会えて本当に嬉しいぞ！";
			link.l1 = "旦那セルヒオ！お会いできるとは思いませんでした！お元気ですか？あの昔ながらの司令官はお変わりありませんか？";
			link.l1.go = "Sergio_21";
		break;
		
		case "Sergio_21":
			dialog.text = "俺は元気だぜ、で、司令官の旦那はロス・テケス鉱山に行っちまった――フアン・コンスンプションとの汚い企みがバレたんだよ。";
			link.l1 = "地雷だと！？まったく驚いたぜ！あいつの件で正義が下るなんて思いもしなかった……";
			link.l1.go = "Sergio_22";
		break;
		
		case "Sergio_22":
			dialog.text = "ああ、そうだったらよかったんだがな、船長……あいつはただ左遷されて降格されただけさ。今は駐屯地で働いてるし、士官の階級すら剥奪されちゃいねえ。まあ、 少なくともサンホセはこのクズを追い出せたってわけだ。";
			link.l1 = "まあ、今のところ順調だな。だが、もっと期待してたんだぜ。";
			link.l1.go = "Sergio_23";
		break;
		
		case "Sergio_23":
			dialog.text = "俺もだよ……でも、あんなクズのことは忘れようぜ――話す価値もねえ。旦那、あんたの船が港に入るって聞いて、急いで桟橋まで駆けつけたんだ。 あんたに持ちかけたい話があるんだぜ。";
			link.l1 = "本当か？聞いてるぜ。";
			link.l1.go = "Sergio_24";
		break;
		
		case "Sergio_24":
			dialog.text = "船長、あんたは信頼できる男のようだな。もう一つ非常に重要なのは、あんたが\n "+GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"")+" それに自分の船もあるんだろう。取引契約を結ぶことを提案するぜ。";
			link.l1 = "面白そうじゃねえか！どんな取り決めだ？";
			link.l1.go = "Sergio_25";
		break;
		
		case "Sergio_25":
			dialog.text = "この話は他の場所で話した方がいいな――灯台の番人小屋でどうだ。あいつは俺の古い友人で、信頼できるやつだ。今日か明日、サンホセの灯台に来てくれ。 そこで待ってるぜ。俺の提案、きっと興味深いと思うぞ！";
			link.l1 = "わかったぜ、セルヒオ旦那。そこで会おう！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Oil_SergioRuntoMayak");
		break;
		
		case "Sergio_26":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Oil_SetSergioToMayakOver.over = "yes"; //снять прерывание
			dialog.text = "またお越しですね、旦那。これからこの件について説明させていただきます。 ";
			link.l1 = "聞いてるぜ。 ";
			link.l1.go = "Sergio_27";
		break;
		
		case "Sergio_27":
			dialog.text = "ご存知かもしれませんが、私は兵士であるだけでなく医者でもあります。なぜかって？それは、 私が教養ある人間だからです。ここで女や酒に時間を浪費せずに済んだのも、教育のおかげです。その代わり、 私はいくつかの探検隊を組織し、この近くで樹脂の鉱床を発見することができました\nこれは戦略的に重要な資源です。この島は、 頑丈で長持ちする船を造るために使われる特別な樹脂が手に入る唯一の場所なのです\n総督と司令官は、私に全ての樹脂をスペイン海軍に売るよう命じました\n問題は、彼らが市場価格の半分しか払ってくれず、他に売ることもできないことです。だからこそ、 あなたに買う機会を提供します。これは非常に重要で、なかなか手に入らない商品なのです。";
			link.l1 = "俺たちの取り決めの条件は何だ？ ";
			link.l1.go = "Sergio_28";
		break;
		
		case "Sergio_28":
			dialog.text = "俺の計算によれば、怪しまれずに月に六十樽は集められるぜ。取引しよう――毎月五日に、この灯台で友達と一杯やることにしてる。樹脂が欲しけりゃ、そこに来てくれ。 一樽につき金のドゥブロン十枚だ。\n全部まとめて一括払い、一度に持っていくんだ。無理強いはしねえ、決めるのはあんた次第だ。どうだ、 話はまとまったか？";
			link.l1 = "俺には最高の取引に聞こえるぜ！もちろん、話はまとまったな！";
			link.l1.go = "Sergio_29";
		break;
		
		case "Sergio_29":
			dialog.text = "素晴らしい。では毎月五日に、俺は古い友人である番人と一緒にカナリアワインを一本飲みながら、 あんたを待っているぜ。";
			link.l1 = "わかった。そうしよう。";
			link.l1.go = "Sergio_30";
		break;
		
		case "Sergio_30":
			dialog.text = "合意に至って嬉しいぜ。またな、船長！";
			link.l1 = "樹脂の商売、うまくいくといいな、旦那！";
			link.l1.go = "Sergio_31";
		break;
		
		case "Sergio_31":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			pchar.questTemp.OilTrade = "true";
			pchar.quest.Oil_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.Oil_fail.win_condition.l1.character = "Sergio";
			pchar.quest.Oil_fail.function = "Oil_TradeFail";
			AddQuestRecordInfo("Unique_Goods", "4");
		break;
		
		case "oil_trade":
			dialog.text = "やあ、旦那船長！樹脂の一束を取りに来たんだろうな。";
			link.l1 = "そうだぜ、セルヒオ旦那。準備はできてるか？";
			link.l1.go = "oil_trade_1";
			link.l2 = "旦那セルジオ、今は取引する気分じゃねえ。後にしてくれ。";
			link.l2.go = "oil_trade_exit";
		break;
		
		case "oil_trade_exit":
			DialogExit();
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "oil_trade_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeOil"))
			{
				dialog.text = "ああ。2550ドゥブロン持ってるか？";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "ああ、ほらよ。";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "運が悪いな！金は俺の船に置いてきちまった。すぐにここへ持ってくるぜ！";
					link.l1.go = "oil_trade_exit";
				}
			}
			else
			{
				dialog.text = "ああ。六百ドゥブロン持ってるか？";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "「ああ、ほらよ。」";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "運が悪かったな！金は俺の船に置いてきちまった。すぐにここへ持ってくるぜ！";
					link.l1.go = "oil_trade_exit";
				}
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && !CheckAttribute(pchar, "questTemp.SergioOilBlock")) // увеличить объём поставок смолами
			{
				link.l4 = "旦那Sergio、もっと樹脂を買いたいんだ。例えば、今の五倍くらいの量をまとめて用意してもらえないか？";
				link.l4.go = "UpgradeOil";
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && CheckAttribute(pchar, "questTemp.SergioOilPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок смолами, если в первый раз не принесли
			{
				link.l4 = "はい、約束通り、セルヒオ旦那、あなたのご要望通り三千ドゥブロンです。\nあなたの先見の明と私の投資があれば、この事業は我々双方にかなりの利益をもたらすと確信しています。";
				link.l4.go = "UpgradeOil_Agreed";
			}
		break;
		
		case "oil_trade_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) RemoveDublonsFromPCharTotal(2550);
			else RemoveDublonsFromPCharTotal(600);
			PlaySound("interface\important_item.wav");
			dialog.text = "お取引できて光栄です、船長。私の部下が樽をあなたの船に積み込むのを手伝います。";
			link.l1 = "ありがとう！";
			link.l1.go = "oil_trade_3";
		break;
		
		case "oil_trade_3":
			dialog.text = "取引はまだ有効だぜ。もし次の分が必要なら、一か月後にまた来な。";
			link.l1 = "ああ、セルジオ。またな。";
			link.l1.go = "oil_trade_4";
		break;
		
		case "oil_trade_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) AddCharacterGoods(pchar, GOOD_OIL, 300);
			else AddCharacterGoods(pchar, GOOD_OIL, 60);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.SergioOil = sti(pchar.questTemp.SergioOil) + 1; // счётчик покупок
		break;
		
		case "UpgradeOil":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Señor"+GetSexPhrase("","「いた」")+"、もっと樹脂を購入したいというご希望は、我々の商売を信頼してくれている証だ。しかし、一つ問題がある\n取引量が増えれば増えるほど、島の当局に目をつけられるリスクも高くなるし、 そういった積荷を管理するには人手や警備も必要だ。正直、それなりに費用もかかる。 もし一度きりで三千ドゥブロンを上乗せしてくれるなら、信頼できる連中を雇って荷を守り、 情報漏洩も防げるようにするぜ。そうすれば航路も安全になり、毎月三百樽の樹脂を供給できる。投資の見返りとして、 今後の全ての取引で卸売業者として十五パーセントの割引も約束しよう。";
				link.l1 = "積荷の護衛に三千ドゥブロンだと？セルヒオ旦那、隠しはしねえが、その値段は信じがたいぜ――まるでピッチの積荷を守るんじゃなくて、エスコリアルで陰謀でも企んでるみてえじゃねえか！";
				link.l1.go = "UpgradeOil_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Señor"+GetSexPhrase("","「いた」")+"、興味を持ってくれてありがたいが、こういった大きな取引には経験と慎重さが必要なんだ。正直に言うと、 貿易の腕前はまだこの規模を扱うには十分じゃない。もう少し経験を積んで、 大口の荷を扱えるようになったらまた来てくれ。そのときに、改めてじっくり話し合おうじゃないか。";
				link.l1 = "わかった。あとでこの件に戻ろう。";
				link.l1.go = "oil_trade_exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeOil_1":
			dialog.text = "Señor"+GetSexPhrase("","「いた」")+"、ご心配はよく分かります。しかし、警備というのは決して安くはありません、 特にこれほど珍しい品物となればなおさらです。それに、俺は情報漏れが絶対にないことを保証するだけじゃなく、 長い目で見れば投資分を取り戻せる割引も用意してますぜ。これで十分な妥協案じゃありませんか？";
			link.l1 = "認めよう。我々の商売では信頼性と秘密厳守には金がかかるし、割引があることで取引が少し魅力的になったのは確かだ。 \nだが、それでも三千ドゥブロンは高すぎる額だ。もう少し値下げできないか？";
			link.l1.go = "UpgradeOil_2";
		break;
		
		case "UpgradeOil_2":
			dialog.text = "残念だが、この手の件で中途半端は許されん。完全な保護を約束するか、すべてを危険にさらすかのどちらかだ。 金額は変わらんし、こうすることでしか確実さと秘密厳守を保証できねえ。王室艦隊全体に、まず俺が、 次にあんたが追われるなんて事態、望まねえだろう？";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "よろしい、サルド旦那、あんたの言う通りだ。安全と信頼にはそれだけの価値がある。三千ドゥブロンだ。ほら、 受け取りな。";
				link.l1.go = "UpgradeOil_Agreed";
			}
			link.l2 = "旦那サルド、あなたの言う対策の必要性は納得したよ。しかし、三千ドゥブロンはかなりの大金で、 今は持ち合わせがないんだ。必要な額が集まるまで待たなきゃならないな。";
			link.l2.go = "UpgradeOil_4";
			link.l3 = "そんな大金があれば、艦隊まるごとや大陸中の兵隊まで買収できるぜ。 松ヤニのささやかな積荷の護衛なんて雇うまでもねえ！悪いが、そんな条件には乗れねえな。 余計なことも追加の出費もせず、今のままでいこうじゃねえか。";
			link.l3.go = "UpgradeOil_3";
		break;
		
		case "UpgradeOil_Agreed":
			dialog.text = "さて、旦那、お互いに信頼し合っているようだな。安心しな、すべてきっちり手配しておくぜ。\n詳しい話だが、いつも通り樹脂300樽が毎月5日にトリニダード灯台で待ってる。\n全部まとめて2550ドゥブロンで買えるぜ。";
			link.l1 = "素晴らしいぞ、セルヒオ旦那。俺をがっかりさせるなよ。";
			link.l1.go = "UpgradeOil_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "4_1");
			pchar.questTemp.UpgradeOil = true;
			pchar.questTemp.SergioOilBlock = true;
			DeleteAttribute(pchar, "questTemp.SergioOilPotom");
		break;
		
		case "UpgradeOil_Agreed_1":
			dialog.text = "疑うなよ、旦那"+GetSexPhrase("","「いた」")+"。すべて最高の水準で手配され、我々の共同の努力は必ず実を結ぶだろう。";
			link.l1 = "じゃあな。";
			link.l1.go = "oil_trade_exit";
		break;
		
		case "UpgradeOil_3":
			DialogExit();
			pchar.questTemp.SergioOilBlock = true;
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "UpgradeOil_4":
			dialog.text = "全額を用意できたら戻ってきな。そしたらまた新しい取引を喜んでしてやるぜ。";
			link.l1 = "「ああ、わかった。」";
			link.l1.go = "oil_trade_exit";
			pchar.questTemp.SergioOilBlock = true;
			pchar.questTemp.SergioOilPotom = true;
		break;
	// <-- генератор смол
		
		case "Juan_abordage":
			dialog.text = "てめえ、何者だ！？";
			link.l1 = "俺の名前は "+GetFullName(pchar)+"「お前のことだがな、消耗野郎、悪魔が待ってやがる――すぐにお前の魂を持っていくぜ！」";
			link.l1.go = "Juan_abordage_1";
		break;
		
		case "Juan_abordage_1":
			if (CheckAttribute(pchar, "questTemp.Consumption.House"))
			{
				dialog.text = "この船はもうすぐ爆発する――火薬庫の導火線にはもう火がついてる――なんで俺たち二人とも死ななきゃならねえんだ？剣を下ろそうぜ。お前は逃げる時間が十分あるし、俺は海に飛び込む――ガレラ岬はここから目と鼻の先だ。金が欲しいなら持ってけ！五百ドゥブロン、現金で――お前は俺のことを忘れ、俺もお前のことを忘れる！どうだ？\n";
				link.l1 = "金か？俺がこれを始めたのは金のためじゃねえ、フアン。クズどもをぶっ殺すためだ。そして、 お前こそが俺にとって最高のご褒美なんだよ。";
				link.l1.go = "Juan_abordage_2";
				link.l2 = "五百ドゥブロン？ふざけてんのか、コンスンプション。どうせここにその倍は隠してるんだろう…今すぐ千枚よこせ、そしたら地獄にでも行きやがれ、さもねえと…";
				link.l2.go = "Juan_abordage_3";
			}
			else
			{
				dialog.text = "船がもうすぐ爆発するから、いい連れができそうだぜ。どう思う？";
				link.l1 = "お前はしゃべりすぎだぜ、コンスンプション、要点を言えよ！";
				link.l1.go = "Juan_abordage_5";
			}
		break;
		
		case "Juan_abordage_2":
			dialog.text = "合意に至ることもできたんだがな……まあ、どうでもいいぜ！";
			link.l1 = "お前はこの哀れな連中を牢から連れ出し、奴らは抵抗も逃げることもできなかった。お前は臆病者だ、コンスンプション。 そして今、臆病者のまま死ぬんだ。";
			link.l1.go = "Juan_abordage_5";
		break;
		
		case "Juan_abordage_3":
			dialog.text = "商売の才覚があるな、友よ……ほら、これが俺の全財産だ。とはいえ、これっぽっちじゃ人生も大したもんじゃねえよな？";
			link.l1 = "お前の命なんざ弾一発の価値もねえ。だからこそ、これが俺の人生で一番うまい取引ってわけだ。さっさと失せろ。";
			link.l1.go = "Juan_abordage_4";
			TakeNItems(pchar, "gold_dublon", 1000);
			Log_Info("You received 1000 doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			OfficersReaction("bad");
			pchar.questTemp.Consumption.TakeMoney = "true"; //атрибут для диалога
		break;
		
		case "Juan_abordage_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "ConJuan_AfterFight_1", 10.0);
		break;
		
		case "Juan_abordage_5":
			dialog.text = "全員を救って俺を殺す時間はもうねえのが残念だな、そうじゃねえか？導火線は燃えてるし、 時間はどんどん無くなっていくぜ…";
			link.l1 = "くそっ！こいつらをここから逃がさなきゃ……\n消え失せろ、このクズども――そのうち報いを受けることになるぜ！";
			link.l1.go = "Juan_abordage_4";
			link.l2 = "それでもやってみるぜ……";
			link.l2.go = "Juan_abordage_6";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
			sld = GetCharacter(NPC_GenerateCharacter("ConAndjelo", "citiz_9", "man", "man", 5, SPAIN, -1, true, "quest"));
			sld.name = "Angelo";
			sld.lastname = "";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
		break;
		
		case "Juan_abordage_6":
			//LAi_SetCurHPMax(NPChar);
			//LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("ConJuan_AfterFight_2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Consumption.KillJuan = "true"; //атрибут для диалога
		break;
		
		case "Waitress":
			dialog.text = "ああ……言葉も出ねえ……なんて悪夢だ！";
			link.l1 = "ああ、俺には何もできなかった。すまねえな、お嬢ちゃん。じゃあな。";
			link.l1.go = "Waitress_1";
		break;
		
		case "Waitress_1":
			DialogExit();
			AddQuestRecord("Consumption", "16");
			AddQuestUserData("Consumption", "sSex", GetSexPhrase("",""));
			Consumption_Close();
		break;
		
		case "Waitress_2":
			dialog.text = "信じられねえ！お前…本当にあいつを助けたのか？どう感謝したらいいかわからねえよ。";
			if (CheckAttribute(npchar, "quest.Consumption.sex"))
			{
				link.l1 = "想像できるぜ、お嬢ちゃん。だが、俺の役目はもう終わった――あとはほんの小さなことだけだ。";
				link.l1.go = "Waitress_3";
			}
			link.l2 = "義務に呼ばれて――俺は動いた。それだけだ。";
			link.l2.go = "Waitress_5";
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan")) AddQuestRecord("Consumption", "18");
			else AddQuestRecord("Consumption", "17");
		break;
		
		case "Waitress_3":
			dialog.text = "俺……ああ、神よ！お前の言う通りだ。約束した通り、あいつのために……上の部屋へ行け――時間があまりないんだ。";
			link.l1 = "じゃあ、急ごうぜ！";
			link.l1.go = "Waitress_4";
		break;
		
		case "Waitress_4"://благодарность натурой
			DialogExit();
			LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "PortSpein_tavern_upstairs", "goto", "goto3", "ConsumptionSexWaitress", -1);
			pchar.questTemp.Consumption.Sex = "true";
		break;
		
		case "Waitress_sex":
			dialog.text = "おう、俺の勇敢なカバジェロ！見ろよ、何を持ってきたと思う？";
			link.l1 = "ほうほう、感心したぜ、さあチェリー酒を開けようじゃねえか！\nそれから他のものも開けてやるよ……今日はお前のラッキーデーだろう？\nハハッ！";
			link.l1.go = "Waitress_sex_1";
		break;
		
		case "Waitress_sex_1":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;
		
		case "Waitress_5":
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
			{
				dialog.text = "お前さんは本物の騎士だな！カバジェロ！ほら――侮辱と思わないでくれ、だがこれを受け取ってほしいんだ。アンジェロを身代金で助けるために集めた金だが、 もう意味はない！どうか断らないでくれ――受け取ってくれ！";
				link.l1 = "そうか、俺はあんたの瞳を覚えておくぜ、セニョリータ――幸せの涙に輝くその瞳は、苦しみの涙よりずっと美しいからな。贈り物、ありがたく受け取るぜ。じゃあな、 アンジェロとあんたに幸運を祈る。";
				link.l1.go = "Waitress_6";
				AddMoneyToCharacter(pchar, 5000);
			}
			else
			{
				dialog.text = "お前は本物の騎士だ！カバジェロ！みんなに話すぜ！俺はずっとお前のことを忘れねえ！";
				link.l1 = "そうかい、そして俺はあんたの瞳を覚えておくぜ、セニョリータ――幸せの涙で輝くその瞳は、苦しみの涙よりずっと美しい。あんたがいつも幸せでありますように。じゃあな！";
				link.l1.go = "Waitress_6";
			}
		break;
		
		case "Waitress_6":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			Consumption_Close();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
