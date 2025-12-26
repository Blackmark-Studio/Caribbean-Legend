// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあればどうぞ。","お聞きしましょう、ご質問は何ですか？"),"これは二度目のご質問でございますが……","これで三度目のご質問ですね……","いつまで続くのですか！？私は植民地の案件で多忙な身ですのに、あなたはまだ私を煩わせるのですか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直しました……","今は駄目だ。場所も時も違う。"),"「確かに……しかし、今ではなく、後で……」","聞いてみよう……だが、もう少し後でな……","申し訳ありません、 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";

			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "あなたの囚人について話したい。";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Hello "+NPChar.name+"、囚人の件で参りました。";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "あなたの囚人について話したいのです。";
					link.l1.go = "CapComission6";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "囚人に関する商売に従事していると伺っておりますが……";
				link.l1.go = "Marginpassenger";
			}
		break;
		
		
		case "CapComission1":
			dialog.text = "ははは。ここに囚人が一人しかいないとでも思っているのか？名を言え。";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+"……彼はここにいますか？";
			link.l1.go = "CapComission2";
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "そうだ。あいつは一週間前にここへ来ていたバルバドスのプランテーションのオーナー、ビショップ大佐に売ったんだ。";
				link.l1 = "くそ……";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				pchar.quest.CaptainComission_SellSlave.over = "yes";
				dialog.text = "ああ、やっと来たか。バルバドスのあのプランテーションの持ち主に彼を売ろうかと考えていたのだが、あの者は一、 二週間でここに来る予定だ……身代金は持ってきたか"+GetSexPhrase("","")+"?";
				link.l1 = "「ご覧ください、」 "+NPChar.name+" …少々問題がありまして……実は、そんなにお金を持っていないのです。しかし、働く意思はございます。";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "彼をまだ売っていないのは良いことです。こちらがあなたの報酬、十五万ペソです。彼はどこにいますか？"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "お前は遅すぎた……それに、なぜ彼のことを気にする？私は彼の親族としか交渉していないのだ。";
			link.l1 = "彼らにここへ来るよう頼まれました。";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "さて、遅かったですね。私には何もできません。";
			link.l1 = "「聞かせてくれ、もし秘密でなければ、いくらであいつを売ったんだ？」"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "ええ、違うさ。でも教えてやらねえよ……言ったら笑うだろう？はははは！じゃあな。";
			link.l1 = "では、また。";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "ほうほう……ちょっとした用件があるのだが……どこから話せばよいか迷っておる。度を越した海賊を沈めねばならぬのだ。";
				link.l1 = "ジャングルで単純に殺すことはできないのですか？";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "「さて、」 "+pchar.name+"「なあ、そう簡単にはいかねえんだよ。金を持って戻ってきたら、その腑抜けを返してやるさ、ははっ。」";
				link.l1 = "よろしい、ではごきげんよう。";
				link.l1.go = "exit";
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					AddQuestRecord("CaptainComission1", "31");
					AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
				}	
				pchar.GenQuest.CaptainComission.RepeatSpeak = true;
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "商売ってのはそういうもんじゃねえんだよ……あいつを殺す必要はねえ、ただ俺の取り分を横取りする奴らに思い知らせてやりたいだけさ。だが、 もしあいつがサメの餌になったとしても、俺は別に気にしねえぜ。";
			link.l1 = "なぜご自身の部下を彼の後に差し向けないのですか？";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "ふむ……さて "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" 何人かの海賊たちに、彼らの分け前は我々の隠し場所――すぐ近くの――に保管されると納得させた "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+"。彼らの二隻の船『"+pchar.GenQuest.CaptainComission.ShipName1+"「」および「」"+pchar.GenQuest.CaptainComission.ShipName2+"「』はつい先ほど錨を上げて出航し、」 "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island+"Abl")+"。これで私がなぜ部下たちにこの任務を任せられないか、お分かりいただけましたでしょうか？";
			link.l1 = "なるほど。私にはどれほどの猶予がございますか？";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12日から15日、それ以上はだめだ。やつらが隠し場所にたどり着かないことが私には重要なのだ。 貴重な積み荷ごと沈めてしまうのは愚かしい。\nその場合は、むしろここに持ってきてもらったほうがよい……";
			link.l1 = "よろしい、引き受けよう。奴らを捕まえてみせる。";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);	
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
		break;
		
		case "CapComission2_3":
			dialog.text = "ご安心ください。私の部下が彼をあなたの船までお連れいたします。それに、なぜ彼のことを気にされるのですか？";
			link.l1 = "私は違います。彼の親族に頼まれて彼を届けに来たのです。";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "ああ、それは結構です。あなたの部下にあんな安値を提示したことを、少し申し訳なく思っていたところです。はははは。 では、ごきげんよう。";
			link.l1 = "では、また。";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));			
			addMoneyToCharacter(pchar, -150000);
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission3":
			dialog.text = "「さて、」 "+GetFullName(pchar)+"、お前、俺の仲間を沈めたのか？へっへっへ……";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "いいえ。捕まえることができませんでした。そして、帰り道でも彼らには会いませんでした。";
				link.l1.go = "CapComission4";
			}
			else
			{
				if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
				{
					link.l1 = "ええ、そうしました。奴らはサメの餌にしてやりました。";
					link.l1.go = "CapComission5";
				}
			}	
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "くそっ！まあ、もうどうでもいい！次のご提案は何ですか？";
			link.l1 = "「もっと簡単な仕事をいただけませんか？」";
			link.l1.go = "CapComission4_1";
			link.l2 = "「聞きなさい、」 "+NPChar.name+"……囚人の値段を下げてください……";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "いいえ。";
			link.l1 = "それでは、御機嫌よう……";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");			
		break;
		
		case "CapComission4_2":
			dialog.text = "値下げしろだと！？お前の無能のせいで俺の隠し財産がなくなっちまったんだぞ！むしろ値上げするべきだろうが！ 欲しけりゃ二十万ペソ払え、嫌ならとっとと出て行け！";
			link.l1 = "高すぎます……それでは、失礼いたします……";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "くそっ、わかったよ、金貨を持っていけ。";
				link.l2.go = "CapComission4_5";
			}	
		break;
				
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "この弱虫を連れて行ってもいいぞ…";
			link.l1 = "ごきげんよう。";
			link.l1.go = "exit";
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
				
		case "CapComission5":
			dialog.text = "ほっほっ！よくやったな！その腑抜けを連れて行け、幸運を祈るぜ。";
			link.l1 = "ありがとうございます。ごきげんよう。";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;
				
		case "CapComission6":
			dialog.text = "金は持ってきたか、チャールズ？あの男をプランテーションに売るって話、冗談じゃなかったんだぞ。";			
			link.l1 = "「聞きなさい、」 "+NPChar.name+"…ですが、問題がございます……私にはそれほど多くのお金がありません。しかし、働く意思はございます。";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "彼をまだ売っていないとは良いことです。これがあなたの報酬――15万ペソです。彼はどこにいますか？"link.l2.go ="CapComission2_3";
			}			
		break;
		
		//Захват пассажиров
		case "Marginpassenger":
			dialog.text = "「それで、私のすることに何のご用ですか？お分かりでしょうが、お引き取りいただいた方がよろしいかと…」";
			link.l1 = "チッ、落ち着け。お前に商談があるんだ。囚人の件についてだ。";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "ああ、よろしい。誰を身代金で解放したいのですか？";
			link.l1 = "お待ちください。私は身代金を払って誰かを買い戻しに来たのではありません、 あなたに囚人を買う機会を提供しに来たのです。ええ、 そしてあなたは彼の身代金を得る機会も手に入れることができます。";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "ふむ。それで、なぜ私の仲介が必要なのですか？ご自身で直接お金を受け取りたいのではありませんか？";
			link.l1 = "私にとってはかなり危険です。役人たちと問題を抱えるかもしれません。";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "ははっ……よろしい。では見せてもらおう。お前の捕虜は誰だ？";
			link.l1 = "これは "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "なるほど。もし嘘でなければ、公正な取引になるでしょう。この男に対して支払いをしてもよいと思います。 "+iTemp+" ペソか、それとも興味深い情報をお渡しすることもできます。お選びください。";
			link.l1 = "この金貨はもらっておくとしよう。もうこんな仕事はうんざりだ……";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "ははっ！もっと話してくれ。きっと私の興味を引く何かがあるのでしょう。";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "金だ。それなら持っていけ。もうお前の問題じゃない。売却対象をここに連れてこい。";
			link.l1 = "彼はもう町の門の近くにいるはずです。ありがとうございます！本当に助かりました。";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "どういたしまして、もっと持ってきてくれ……ではまた！";
			link.l1 = "ご武運を……";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			ref sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT + FLAG_GOODS_TYPE_UNIQUE, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "利口な男と取引できて嬉しいです。さて、よく聞いてください。数日後に\n "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" 本土からスペインの遠征隊が貴重な品を積んで到着する予定です。彼らはその貨物を運ぶ船を待っています。 一週間以内に現地へ行けば、その貨物を手に入れるチャンスがございます。\n私があなたの立場なら、すでに自分の船へ向かっていることでしょう。そして、囚人をここへ連れてきてください。";
					link.l1 = "ありがとうございます！品物は私の苦労に見合う十分な報酬でございます。\nそして、私の乗客は今ごろ町の門の近くにいるはずです。すぐにお連れいたしましょう。";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "賢い男と取引できて嬉しいです。さて、聞いてください：約一週間後に、スペインのブリガンティン『"+pchar.GenQuest.Marginpassenger.ShipName1+"「」は貴重な品を積んで、～から出航する "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" へ "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+"。急げば、すぐに追いつけますぞ。\nまだここにおられるのですか？私があなたの立場なら、もう自分の船へ向かっているでしょう。それから、 囚人をここへ連れてきてください。";
					link.l1 = "ありがとうございます！品物は私の苦労に見合う十分な報酬でございます。\nそして、私の乗客は町の門の近くにいるはずです。すぐにお連れいたしましょう。";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen"));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
