// диалог официантки
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk1, bOk2;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bOk1 = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption")  && bOk1)
				{
					dialog.text = "何をご用でしょう、旦那？申し訳ありません、私はただ……「すすり泣き」……ああ……ごめんなさい。";
					link.l1 = "どうしてそんなにお困りなのですか、お嬢様？こんなに美しいお顔に涙を浮かべて……何があったのですの？";
					link.l1.go = "Consumption";
					break;
				}
			}
			//<-- Цена чахотки
			
			// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
			if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
            {
				DelMapQuestMarkCity("PortPax");
				DelLandQuestMark(npchar);
				PlaySound("Voice\English\Enc_RapersGirl_1.wav");
				dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! "+UpperFirst(GetAddress_Form(NPChar))+"「助けてくれ！殺人だ！」";
				link.l1 = "は？誰を殺したって？どこでだ？冗談かい、あんた？";
				link.l1.go = "FMQP";
				break;
			}
			
			//--> Тайна Бетси Прайс
			if (npchar.location == "Villemstad_tavern" && CheckAttribute(pchar, "questTemp.TBP_BetsiPrice") && !CheckAttribute(pchar, "questTemp.TBP_BetsiPrice_Sex"))
			{
				bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
				bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
				if (bOk1 || bOk2)
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"！また会えて本当に嬉しいよ…来てくれてありがとう…でも、残念ながら今は話すにはあまり良い時じゃないんだ。一人になった時にまた来てくれ。その時に…もっと個人的な話ができるから。";
							link.l1 = "話せて楽しかったが、そろそろ行かないといけない。またどこかで会えるかもしれないな。";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"…あんたがうちの酒場への道を忘れちまったんじゃないかと思い始めてたぜ。\n一人じゃないのが残念だな。二人きりで話せるかと期待してたんだが。";
							link.l1 = "運命がまだ私たちに二人きりで話す機会を与えてくれると思います。";
							link.l1.go = "exit";
						break;
					}
				}
				else
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"！待たせすぎないって信じてたよ。もう一分たりとも無駄にしたくないんだ。\n二階の部屋は空いてる……あたしたちだけのためにね。断るつもりじゃないでしょ？";
							link.l1 = "俺をその気にさせるのが上手いな……まあ、断る理由もねえ。どうする？";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "申し訳ないが、今日は本当に大事な用事があるんだ。\nでも約束するよ、次は必ず埋め合わせをするからな。";
							link.l2.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"！待たされるのを楽しんでいるのかと思い始めていたよ。\nまさか、像みたいにそこに突っ立っているつもりじゃないだろうな？\nこの時間をもっと有意義に使う方法はいくらでもあるんだぜ。";
							link.l1 = "誰もあなたの魅力には抗えないよ……時間を無駄にする必要はない、今すぐ上の階に行くよ。";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "お前はなかなかの誘惑者だな、ベッツィ……だが残念ながら、今は他に行かねばならないんだ。";
							link.l2.go = "exit";
						break;
					}
				}
				link.l9 = "いくつか質問したいんだ。";
				link.l9.go = "quests";
				break;
			}
			//<-- Тайна Бетси Прайс
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "上の階に行くように言っただろう。ここにいないで、目立つな。";
					link.l1 = "わかったよ、行くぜ。お前に迷惑かけたくねえからな…";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "俺はここに来たばかりだから、頼むから仕事の邪魔をしないでくれ。まだ全然慣れてないんだ……";
					link.l1 = "「それで、君の前にここで働いていたウェイトレスはどこにいるんだ？」 "+pchar.questTemp.different.FackWaitress.Name+"……私の記憶では……";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = "また来てね、坊や。もっと楽しいことができるかもしれないわ。時間がもう少しあればいいのにね……";
					link.l1 = "もちろんだ、あんたは最高だったぜ！";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = "俺はあんたのこと知らねえんだ、だから俺にかまうなよ…";
					link.l1 = "俺の金はどこだ！？";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "「すまねえ」 "+GetSexPhrase("イケメン","かわいこちゃん")+"、今は忙しすぎるんだ。酒場にはいい時間だが、話してる暇はねえ！";
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "お願いです、船長、ここで喧嘩しないでください！この場所を掃除するのは大変なんです。";
					link.l1 = ""+GetSexPhrase("ふん…俺は最初からそのつもりはなかったぜ。","俺がケンカを探してる酔っ払いに見えるか？あたしはあんたと同じただの娘だよ、心配すんな。")+"";
					link.l1.go = "exit";
				break;

				case 2:
					if (hrand(1) == 0) // Addon-2016 Jason
					{
						dialog.text = ""+GetSexPhrase("おお、船長！今夜は私と一緒に寝ない？自慢じゃないけど……","座ってくれ、船長。お前みたいな本物の海の狼に会えるのはいつだって嬉しいぜ。")+"";
						link.l1 = "今は急いでるんだ、残念だがな。\n次の機会にしようぜ！";
						link.l1.go = "exit";
						bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) || npchar.city == GetLadyBethCity(); // 291112
						if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk)
						{
							link.l2 = "喜んでだぜ、嬢ちゃん！";
							link.l2.go = "Love_1";
						}
					}
					else
					{
						dialog.text = "座ってくれ、船長。うちのラムを飲んで、カードやサイコロでも遊んでいきな。くつろいでくれよ！ 本物の海の狼に会えるのはいつだって嬉しいもんだぜ。";
						link.l1 = "「ありがとう、かわいこちゃん。」";
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = "何か注文したいなら主人に話しかけてくれ。カウンターの奥にいるぜ。";
					link.l1 = "助言ありがとう。";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "休んで体力を回復したいなら、部屋を借りな。\n一晩中ホールにいても大して役に立たねえぜ。";
					link.l1 = "感謝する。";
					link.l1.go = "exit";
				break;
			}			
			link.l9 = "いくつか質問したいんだ。";
			link.l9.go = "quests";//(перессылка в файл города)
		break;
		
        case "Love_1":
			dialog.text = "では聞け。ここ酒場で部屋を借りろ。そこへ行って俺を待っていろ。後でこっそり忍び込むからな…";
			link.l1 = "ははっ！任せとけ、あんた！待ってるぜ！";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = hrand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
		break;
		
        case "Love_IDN":
			dialog.text = "彼女はもうここで働いていません、引退しました……すみません、私はやるべき仕事があるんです。";
			link.l1 = "……わかった……";
			link.l1.go = "exit";
		break;
		
        case "Love_IDN_1":
			dialog.text = "よく聞け、このスケベ野郎。お前の金がどこにあるかなんて知らねえよ！これ以上しつこくするなら衛兵を呼ぶぞ、 そうしたらお前は牢屋行きだ！";
			link.l1 = "「結構だ、護衛はいらねえ……なんて間抜けだ……」";
			link.l1.go = "Love_IDN_2";
		break;
		
        case "Love_IDN_2":
			dialog.text = "まさに、その通り、あんな馬鹿者だ。次はもっと賢くてまともになるんだな。";
			link.l1 = "やってみるさ……（小声で）くそったれのあばずれめ……";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "俺の声が聞こえるか？";
			link.l1 = "ううっ……";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "具合が悪いのか？頭が痛いのか？";
			link.l1 = "くそっ……ここはどこだ？";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "覚えてないのか？あいつらがお前を襲ったんだ。";
			link.l1 = "何だと？ああ…頭が…誰がこんなことをしやがったんだ！？";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "知るかよ？奴らが押し入ってきて、殺すぞと脅して、お前のポケットを調べて、さっさと行っちまったんだ。";
			link.l2 = "そうか……くそ……水が欲しい……ありがとう。";
			link.l2.go = "exit";
		break;
		
		//--> Jason Цена чахотки
		case "Consumption":
			npchar.quest.Consumption = "true";
			dialog.text = "いいえ、なんでもありません、旦那……ご親切に感謝しますが、でも私……（泣く）";
			link.l1 = "誰かに嫌なことをされたのか？落ち着いて、お嬢ちゃん、全部話してごらん。";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "いや、いや、旦那、なんでもないんだ。無礼を許してくれ、ただ……兄のことなんだ。兄は死んだって言われてるけど、俺は信じられない。何を信じればいいのか分からないけど、 心の奥で兄が大きな困難に巻き込まれていると感じるんだ。両親が亡くなってからはアンジェロしかいないのに……（泣く）";
			link.l1 = "わかりましたが、どうか落ち着いてください。あなたの兄弟に何があったのですか？";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "旦那…誤解しないでください。でも、どうしてそんな立派な船長が、 酒場の普通で控えめな娘なんかに気をかけてくださるんですか？私、 助けていただいてもお礼に差し上げられるものなんて何もありません… ";
			link.l1 = "実際、その通りだな。無私なんて俺には向いてねえ、だから強くなれよ、誰だって身内を失うもんだ。フランスじゃ 「セ・ラ・ヴィ」って言うんだぜ……";
			link.l1.go = "exit";
			link.l2 = "女はいつだって男に感謝する方法を見つけられるものさ……はは。さあ、もう泣くのはやめて、あんたの悩みを話してくれ。";
			link.l2.go = "Consumption_3_1";
			link.l3 = "若いセニョリータ、我々の教会が互いに助け合うことを教えているのをご存じないのですか？もちろん、 私にできることならお手伝いしましょう。";
			link.l3.go = "Consumption_3_2";
		break;
		
		case "Consumption_3_1":
			if(sti(pchar.reputation.nobility) > 36)
			{
				Notification_Reputation(false, 36, "high");
				dialog.text = "それは「ヒント」だったのか？失礼、あなたと話したのは俺の間違いだった！さらばだ、「旦那」…";
				link.l1 = "お望みのままに、あなた。";
				link.l1.go = "exit";
			}
			else
			{
				Notification_Reputation(true, 36, "high");
				dialog.text = "そうか……少なくとも望みには正直だな。アンジェロを見つけるか、彼に本当に何があったのかを教えてくれたら、 頼んだものを必ず渡そう……";
				link.l1 = "親愛なるセニョリータ、あなたと取引できて光栄です……さて、さっそくあなたの兄上の話に入りましょう。";
				link.l1.go = "Consumption_4";
				npchar.quest.Consumption.sex = "true";
			}
		break;
		
		case "Consumption_3_2":
			dialog.text = "冗談じゃねえだろうな？本当にタダで俺を助けたいってのか？";
			link.l1 = "泣いている娘を助けないのは悪い奴だけだぜ。心配するな、俺は本当にお前を助けたいんだ。 アンジェロに一体何があったんだ？";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "わかりました、旦那。兄は……ああ、涙をこらえるのが辛いんです、ごめんなさい……私の……仕事がうまくいかなかったせいで、本当に貧しかったんです……それでアンジェロは地元の密輸業者と働き始めました。彼は自分の小さな漁船で、 税関を避けて何かを運べばもっと稼げると思ったんです。";
			link.l1 = "簡単に言えば、お前の兄貴は犯罪者になったってことだろ？";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "いいえ、旦那、あなたは分かっていません……彼はそんな人じゃないんです！彼は私のためにやったんです！ここでこっそり金を稼ぐのをやめさせるために……分かりますよね。私たちは借金を抱えていて、彼は私の名誉と魂のためにやったんです。それで……彼は捕まってしまいました。大した問題じゃなかったんです、 私は彼の釈放金を払うためにさらにお金を借りたくらいです……でも、彼は死んだと言われました。";
			link.l1 = "奴らが言ったって？誰が言ったんだ？それに、なぜ信じないんだ？あいつは牢獄で死んだのか？";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "はい。彼の釈放金を持って行ったとき、司令官はアンジェロが肺病で死んだと言ったのです。考えてみてください！ 彼は元気な状態でそこに着いたのに、たった二週間後にあの牢で亡くなったのです。あの人たち…遺体を見ることさえ許してくれませんでした。疫病を防ぐために、 要塞のそばの湾のすぐ近くに囚人たちを埋葬したと言われました。";
			link.l1 = "疫病か？それは十分あり得る話だな。で、単に信じたくないだけなのか、それとももっと深刻な理由があるのか？";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			dialog.text = "いや…いやだ！（泣きながら）馬鹿みたいに聞こえるかもしれないけど、もし彼が死んだなら、私には絶対に分かるはずなの。 アンジェロはいつも強かった――本物の船乗りだったわ。でも、もう一つだけ言わせて\n私の祖父は私が子供の頃に肺病で亡くなったの。おじいちゃんは年寄りだったけど、何年も病気と闘っていた！ 私はよく知ってるの、肺病は数日で人を殺したりしないわ、信じて！";
			link.l1 = "ふむ……お前のせいで俺も疑い始めちまった、ここは何かおかしいな。約束はできねえが、もう少し調べてみるぜ。";
			link.l1.go = "Consumption_8";
		break;
		
		case "Consumption_8":
			dialog.text = "たとえ簡単な約束でも、私が期待していた以上のものです！あなたは本当に親切ですね、旦那！ここでお待ちしています！ ";
			link.l1 = "ああ、若さよ！なんと気まぐれな感情だろう……お嬢さん、よければその手を返してくれないか、まだ必要なんだ、ははは……さて、それじゃあ、ちょっと見て回ってくるよ。";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			DialogExit();
			npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Consumption = "begin";
			AddQuestRecord("Consumption", "1");
		break;
		//<-- Цена чахотки
		
		// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
		case "FMQP":
			dialog.text = "冗談じゃない！上の階だ！チンピラ二人が貴族を殺そうとしてるんだ！助けてくれ、船長！ ここで武器を持ってるのはあんただけなんだ！";
			link.l1 = "外に走って、衛兵を呼べ！俺は二階に行くぞ！";
			link.l1.go = "FMQP_1";
			link.l2 = "お嬢さん、私を衛兵と間違えたのでしょう。殺人事件なら巡回隊を呼びなさい。";
			link.l2.go = "FMQP_exit";
		break;
		
		case "FMQP_exit":
			dialog.text = "あ、ああ、衛兵！助けてくれ！";
			link.l1 = "...";
			link.l1.go = "FMQP_exit_1";
		break;
		
		case "FMQP_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
			LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
			SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
		break;
		
		case "FMQP_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			pchar.quest.FMQP_room.win_condition.l1 = "locator";
			pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
			pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.FMQP_room.function = "FMQP_InRoom";
		break;
	}
}
