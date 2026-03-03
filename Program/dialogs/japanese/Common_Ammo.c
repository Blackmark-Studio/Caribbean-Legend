// диалог коменданта форта
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
   /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "First time":
			location = &Locations[FindLocation(pchar.location)];
			if (rand(4) == 4 && GetNpcQuestPastDayParam(location, "gun_date") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("聞いてくれ、大事な用件があるんだ。君が手を貸してくれるといいんだが。","船長、かなり儲かる話にご興味ありませんか？"),RandPhraseSimple("お前さんなら大事な件で力を貸してくれると思うぜ。","船長、あなたに繊細な提案があるんだが、俺たち二人にとってかなり儲かる話かもしれねえぜ。"));					
				link.l1 = "さあ、言いたいことを言えよ、どうなるか見てやろうじゃねえか…";
				link.l1.go = "GiveTaskGun";
				location.quest.PrisonGun = "Target"; 
				SaveCurrentNpcQuestDateParam(location, "gun_date");
				break;
			}
		
			dialog.text = RandPhraseSimple("私はこの要塞の司令官だ。ここで何の用だ？","何の用だ？なぜここに来たんだ？");
			link.l1 = "ああ、なんでもねえよ、ただ町やその周りを見て回ってるだけだ。ここには本当にたまたま来ただけさ。";
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "要塞へようこそ、船長。何かご用ですか？";
				link.l1 = "いや、何もない。ただ何となく立ち寄っただけだ。";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "ごきげんよう、副提督！ご命令はございますか？";
				link.l1 = "いいや、役人さん、命令なんてない。ただ砦を見に来ただけだ。";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "総督閣下！砦は完璧な状態でございます。ご命令はございますか？";
				link.l1 = "無事でよかったな、士官。命令はない、ただ砦の様子を見に立ち寄っただけだ。";
			}
			// <-- legendary edition
			link.l1.go = "exit";
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_ammo" && GetQuestPastDayParam("questTemp.Wine_bottle") < 5)
			{
				link.l11 = "おもしろい情報があるんだ、士官殿。お前の部下の一人が、 "+pchar.questTemp.Wine.SName+" 町でワインを私の仲介で購入してほしいと頼まれました。あなたのご命令を考慮すると……";
				link.l11.go = "Wine_prison";
			}
			// <-- мини-квест Дефицитный товар
			// Карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "fraht" && NPChar.location == "portpax_ammo")
			{
				link.l11 = "こんにちは、役人さん。私はバステール植民地から来た、ジェラール・ルクロワという男の命令で来たんだ。 俺の船倉に火薬と爆弾の積荷があんたのために積んであるぜ…";
				link.l11.go = "trial";
			}
			// Опасный груз -->
			if (pchar.location == "Cumana_Ammo")
			{
				if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
				{
					link.l2 = "心配そうな顔をしているな、士官殿。どうした、俺にできることはあるか？";
					link.l2.go = "zpq_prs1";
				}
				if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 15000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
				{
					link.l3 = "火薬の全積荷が無事に届けられたことをご報告できます。\n私の船は荷下ろしの準備ができています。";
					link.l3.go = "zpq_ex";
				}
				if (pchar.questTemp.zpq == "begin")
				{
					link.l4 = "火薬の取引をやめたいんだ。こんなの面倒すぎる。";
					link.l4.go = "zpq_fld2";
				}
			}
			// <-- Опасный груз
			NextDiag.TempNode = "First time";
		break;

		// --> Орудия для форта
		case "GiveTaskGun":
			dialog.Text = LinkRandPhrase("ご覧の通り、砦の大砲はかなり老朽化しています。財務局から新調のための資金は割り当てられましたが、正直なところ、 どこで新しい大砲を購入すればいいのか全く見当がつきません。我々 の植民地では必要な数を手に入れるのは到底無理です。そこで、 あなたが拿捕した船の砲をこちらで活用できるのではないかと考えたのです。","砦の砲台を交換しなければならん。資金はすでに割り当てられているが、わかるだろう…我が植民地では必要な数を手に入れるのは到底無理なんだ。","使い古された砦の大砲を交換する任務を受けたんだが、どこを探しても十分な数が見つからねえんだ。");
			Link.l1 = "ふむ……もう少し詳しく教えてくれないか？口径、数量、値段は？";
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;
			
		case "GiveTaskGun_1":
			GetGunType();
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price)*sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			dialog.Text = "必要だ "+pchar.questTemp.PrisonGun.Text+"、の額で "+sti(pchar.questTemp.PrisonGun.Qty)+"  「ちょうどその数の単位だ。支払いは金のドゥブロンでやるぜ。」 "+sti(pchar.questTemp.PrisonGun.Price)+" 一つにつき。それで合計は "+FindRussianDublonString(sti(pchar.questTemp.PrisonGun.Sum))+" 全部で、ということだ。どうだ？ああ、それともう一つ――全部まとめて買うが、金がまだ届いていないから、受け取るのは一か月後になるぞ。";
			Link.l1 = RandPhraseSimple("いいえ、役人さん、あなたの申し出には全く興味がありません……申し訳ない。","魅力的だが、遠慮しておくよ。理由は俺の胸の内に留めさせてくれ。");
			Link.l1.go = "exit_gun";
			Link.l2 = RandPhraseSimple("ふむ、その申し出は確かに興味深いな。取引成立だ。","まあ、引き受けるとするか。そんなに難しくないし、明らかに儲かりそうだ。");
			Link.l2.go = "GiveTaskGun_2";
		break;
			
		case "exit_gun":
			dialog.Text = "残念だな、船長、お前に期待してたんだぜ。\nそれと…この話は砦の中だけにしてくれるよな？";
			Link.l1 = "そのことをいちいち言われなくてもわかってる。よろしく頼む。";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
			
		case "GiveTaskGun_2":
			dialog.Text = "よし、それで決まりだ！特に条件は設けないが、半年以上かからないように頼むぞ。\nそして、これは極秘事項だということは理解しているな？";
			Link.l1 = "もちろんだ。では、司令官、またな。";
			Link.l1.go = "exit";
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First time";
		break;	
		
		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = "「一ヶ月経つ前に戻ってくるなと言っただろう！」";
				Link.l1 = "くそっ！俺はあまりにも忙しかったんだ"+GetSexPhrase("","")+"、俺は～を失った"+GetSexPhrase("","")+" 時間を忘れてしまった……すまない、約束通り後でまた来るよ。";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = "ふむ……知っているか、俺たちが“取引”をした日からもう半年以上経っているんだぜ。大砲はもう買っておいた。まさか、 いつまでもお前を待っているとでも思ったのか？";
				Link.l1 = "くそっ！で、今さらこいつらをどうしろってんだよ？";
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); // город
			
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.Text = "ああ、手伝う準備はできているか？";
				if (amount < 0)
				{
					Link.l1 = "いや、まだ進行中だ。ただ、俺たちの取引がまだ有効か確認したかっただけだ。";
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = "そうだ。全部の積み荷は船倉にある―― "+sTemp+" 約束通りの部隊だ。";
					Link.l1.go = "TakeGun";
				}
			}
			else 
			{
				dialog.text = "港にお前の船が見当たらねえな。まさかあの大砲をジャングルの中引きずって行けってのか？ 急いで俺たちの港に戻って来い。";
				link.l1 = "俺の船は島の反対側にあるんだ。港まで持ってくるぜ。";
				link.l1.go = "exit";
			}
		break;
		
		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
				dialog.Text = RandPhraseSimple("あのさ、本当に気まずいんだけど、取引から手を引かないといけなくなったんだ。\nちょうど財務監査が入ってさ、あいつらこういうことにはやたら厳しいだろ。\nどうにもできないんだ。すまない。","船長、ご存知の通り……まあ、本国から大砲が送られてきて、当然ながら俺はそれを買わざるを得なかったんだ。法外な値段だったが……本当に申し訳ない、あなたをがっかりさせてしまって……俺も気が重いんだ。");
				Link.l1 = "くそっ！で、今さらこいつらをどうしろってんだ？";
				Link.l1.go = "TakeGun_no";
			}
			else
			{
				dialog.Text = RandPhraseSimple("素晴らしい。駐屯地から分隊を派遣して荷下ろしさせよう。","素晴らしい。私の兵士たちが大砲の荷下ろしを手伝います。");
				Link.l1 = "支払いの用意はできたか？";
				Link.l1.go = "TakeGun_1";
			}
		break;
		
		case "TakeGun_no":
			dialog.Text = "知らねえな。造船所で売るか、商船を装備するか、沈めちまうか……本当に分からねえ。頼むから、この取引のことは誰にも言わないでくれよ。";
			Link.l1 = "おやまあ、そうなのかい！まったく言葉も出ないよ！";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_late":
			dialog.Text = "俺には関係ねえ。お前の問題だ。売ろうが、捨てようが、沈めようが――本当にどうでもいいぜ。";
			Link.l1 = "ああ、まったく時間の無駄だったな……";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = sti(pchar.questTemp.PrisonGun.Sum);
			dialog.Text = "もちろんだ。ほら、金貨だ―好きにしな。";
			Link.l1 = "ありがとうございます！お取引できて光栄でした！";
            Link.l1.go = "TakeGun_2";
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(sti(pchar.questTemp.WPU.Escort.Money))+"");
			PlaySound("interface\important_item.wav");
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;
		
		case "TakeGun_2":
			dialog.Text = "私も同じ気持ちだ。君はとても助かったよ。\nそれから、頼む、この取引はこの部屋だけの話にしてくれ。";
			Link.l1 = "もちろんです。ご多幸をお祈りします。";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		// <-- орудия для форта

		//Jason --> мини-квест Дефицитный товар
		case "Wine_prison":
			dialog.text = "何だと！？砦内での飲酒は厳禁だと厳しく命じておいたはずだ！まあ、奴にはその責任を取らせる。奴の報酬から1000ペソ差し引いて、お前の用心深さへの褒美として渡そう。\nそしてこの男は三日間拘留されることになる。";
			link.l1 = "ありがとうございます。 "+GetAddress_FormToNPC(NPChar)+"。こうした違反を止めるのは我々皆の共通の義務だ。";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1000);
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			pchar.quest.Wine_Exchange.over = "yes";//снять прерывание
			pchar.quest.WineTraderQM.over = "yes";//снять прерывание
			WineTraderQMDel();
			sld = characterFromId(pchar.questTemp.Wine.id);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			NextDiag.TempNode = "First time";
		break;
		// <-- мини-квест Дефицитный товар
		
		// Карибские нравы
		case "trial":
			iTest = FindColony(NPChar.City); // город
			QuestPointerDelLoc("portpax_town", "reload", "gate_back");
			QuestPointerDelLoc("portpax_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("portpax_fort", "reload", "reload2");
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetSquadronGoods(pchar, GOOD_BOMBS) < 2500 || GetSquadronGoods(pchar, GOOD_POWDER) < 2500)
				{
					dialog.text = "ふむ。しかし、このバッチは満杯じゃねえ！どうしてこうなったんだ？";
					link.l1 = "くそっ！どうかお許しください、俺のせいです。すぐに足りない分を買い足して、約束通り全部まとめてお渡しします。";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "お前が俺たちの運び屋か？よし。まずは貨物の確認を済ませてから、次の指示を出すぜ。";
					link.l1 = "「いいだろう。」";
					link.l1.go = "trial_1";
				}
			}
			else
			{
				dialog.text = "港にお前の船が見当たらねえな。まさか積み荷をジャングルの中引きずって運べってのか？ さっさと俺たちの港に来て戻ってこい。";
				link.l1 = "俺の船は島の反対側にあるんだ。港まで持ってくるぜ。";
				link.l1.go = "exit";
			}
		break;
		
		case "trial_1":
			if(!bImCasual) pchar.quest.Trial_FrahtFail.over = "yes"; // belamour legendary edition если был - снять таймер
			dialog.text = "よし、火薬と爆薬、それぞれ2,500ユニット……いいだろう。兵士たちが荷を降ろすから、お前の連中は休んでていいぜ。これが運送の報酬だ――五千ペソだ。";
			link.l1 = "ありがとう！次は何をすればいい？ルクロワ旦那が言ってたんだが…";
			link.l1.go = "trial_2";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_2":
			AddMoneyToCharacter(pchar, 5000);
			RemoveCharacterGoods(pchar, GOOD_BOMBS, 2500);
			RemoveCharacterGoods(pchar, GOOD_POWDER, 2500);
			dialog.text = "はいはい、これから指示を伝えるぞ。ちゃんと聞く準備はできているか？";
			link.l1 = "「ああ、役人さん。」";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "つまり、我々の軍艦『ウォーライク』は、スペイン領ポルトベロ、スペイン本土南部付近を巡航中だ。 この艦はフロリアン・ショークの指揮下にあり、 二週間後にポルトベロを出港する予定のスペイン重ガレオン船を待ち伏せする準備をしている。\n問題は、我々のフリゲート艦の大砲に鋳造不良が発生しており、 作戦を成功させるには十五門の大砲を交換しなければならないことだ。さもなければ、ガレオン船は『ウォーライク』 よりも火力でも人員でも上回ってしまう。\nもし大砲の交換ができなければ、フロリアン・ショークは何の成果も得られずに退却を余儀なくされる。 このような事態は絶対に避けたい。君の任務は、十四日以内に十五門の大砲を届けて作戦を成功させることだ。";
			link.l1 = "つまり、十五門の大砲を積み込んでポルトベロへ向かい、フリゲート艦『ミリタント』 を探してフロリアン・ショーク船長に大砲を引き渡せばいいんだな？";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "その通りだ。よくわかったな。この任務を引き受ける覚悟はできているか？";
			link.l1 = "「支払いはどうするんだ？」";
			link.l1.go = "trial_5";
			link.l2 = "申し訳ありません、旦那、ですが私は関わりたくありません。どうかご容赦ください。";
			link.l2.go = "trial_exit";
		break;
		
		case "trial_exit":
			dialog.text = "あなたにはその権利があるが、同意してくれると思っていたんだ。\nだが、これで別の運び屋を探さなきゃならないな、もう時間もあまり残っていないし……\nまあ、これ以上引き止めはしないよ、船長。";
			link.l1 = "よろしくお願いします。";
			link.l1.go = "trial_exit_1";
		break;
		
		case "trial_exit_1":
			DialogExit();
			AddQuestRecord("Trial", "6");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "trial_5":
			dialog.text = "そのことは心配するな。フロリアン・ショークが船の財宝から金のドゥブロン二百枚をお前に払うだろう。それに、 きっと彼はお前とお前の船を自分の目的のために使いたがるはずだ――もちろん、お前が同意すればの話だがな。";
			link.l1 = "よし、この任務は俺に任せろ！大砲はどこだ？";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "すぐに兵士たちに命じて、それらをあなたの船に積み込ませます。できるだけ早く出航してください、旦那！ご武運を！";
			link.l1 = "ありがとう。運も追い風もあって困ることはないからな……";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			DialogExit();
			AddQuestRecord("Trial", "7");
			pchar.questTemp.Trial = "cannon";
			// belamour legendary edition
			if(!bImCasual) SetFunctionTimerCondition("Trial_CannonFail", 0, 0, 21, false); 
			else NewGameTip("Exploration mode: timer is disabled.");
			SetCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24)+15);
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				EnemyNationHunterOnMap(true);//запуск перехватчиков
			}
			pchar.quest.Trial_cannon.win_condition.l1 = "location";
			pchar.quest.Trial_cannon.win_condition.l1.location = "Portobello";
			pchar.quest.Trial_cannon.function = "Trial_CreateFlorianFrigate";
			// Sinistra - квест "Встреча с Диего"
			bDisableFastReload = true;
			PChar.quest.VsD_GiumDyubua.win_condition.l1 = "location";
			PChar.quest.VsD_GiumDyubua.win_condition.l1.location = "PortPax_Fort";
			PChar.quest.VsD_GiumDyubua.win_condition = "VsD_GiumDyubua";
			AddMapQuestMarkShore("Shore47", false);
		break;
		
		// Опасный груз -->
		case "zpq_prs1":
			if(!isBadReputation(pchar, 70))
			{
				dialog.text = "ふむ、そうかもしれん。まあ、お前の評判がいいから、今回は賭けて信じてみることにするぜ。そうじゃなきゃ、 こんな話は持ちかけもしねえ。実はな、かなり大量の特別な積み荷が必要なんだ。だから、 大きな船と危険を冒す覚悟がいる。それと、絶対に誰にもこのことを漏らさないと約束してくれ。\nもし気が進まねえなら、今すぐ言ってくれ。俺の言いたいことは伝わったと思うぜ…";
				link.l1 = "面白そうだな。報酬がまともなら乗るぜ、ただし何の積み荷かはさっぱり分からねえがな。ま、 とにかく俺の言葉は信じてくれ。";
				link.l1.go = "zpq_prs2";
				link.l2 = "いや、やめとくぜ……俺が約束したら働かなきゃならねえだろ、それは面倒くせえからな。やらねえよ。";
				link.l2.go = "zpq_fld";
				Notification_Reputation(true, 71, "low");
			}
			else
			{
				dialog.text = "あなたの評判は私には受け入れられません。\n部屋を出ていただきたい。\n我々は自分たちで問題を解決できます。";
				link.l1 = "どうでもいい、なら自分で解決しろ…";
				link.l1.go = "exit";
				Notification_Reputation(false, 71, "low");
			}		
		break;
		
		case "zpq_fld":
			dialog.text = "まあ、少なくとも正直に俺を断ってくれたな……もう引き止めはしねえよ。";
			link.l1 = "さらば。";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_fld2":
			dialog.text = "ふむ、正直お前にはそんなこと期待してなかったぜ。出て行ってもらうしかねえな……それと、情報を漏らさないって約束、忘れるなよ。";
			link.l1 = "申し訳ない……";
			link.l1.go = "exit";
    		ChangeCharacterComplexReputation(pchar,"nobility", -3);
			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		
		case "zpq_prs2":
			dialog.text = "素晴らしい。素晴らしい。しかし問題は、最近の嵐で砦の兵器庫にある火薬の備蓄が損傷を受けたことだ。\nこの状況がどれほど繊細な問題か、君に説明する必要はないだろう。\nもし長期の包囲戦になれば、砦は何もできなくなる。\n我々は長くは持たない。";
			link.l1 = "なるほど。どんな積荷が必要なんだ、それと量はどれくらいだ？";
			link.l1.go = "zpq_prs3";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_prs3":
			dialog.text = "火薬が一万五千樽必要だ。十万ペソを支払おう…これは非常に良い値段だと理解してほしい。今の状況では、こうした出費を受け入れざるを得ないのだが、 総督の会計係を説得するのは難しかった…\n嵐の季節で自前の補給線は使えないし、この問題を皆に知られたくもないのだ…";
			link.l1 = "なるほど……値段は本当にいいな。リスクについて言ってたな……";
			link.l1.go = "zpq_prs4";
		break;
		
		case "zpq_prs4":
			dialog.text = "私は、これほど大量の火薬は運搬中に非常に危険になり得ると言いたかったのだ。私自身、 何度か爆発を目の当たりにしたことがある；時にはたった一つの火花で十分なんだ。\nだが、もし嵐に遭遇したら……通常、船団全体が火付け船の可能性がある船からは距離を取るものだ。もし爆発すれば、全員が死ぬことになる！";
			link.l1 = "なるほど……だが俺はいつも約束を守る。任せておけ。";
			link.l1.go = "zpq_prs5";
			link.l2 = "さて、旦那……あんたがそんなひどい話ばかりするもんだから、もうその仕事をやる気が失せちまったよ。";
			link.l2.go = "zpq_fld2";
		break;
		
		case "zpq_prs5":
			dialog.text = "よし、取引が成立してとても嬉しいよ。貨物を持ってきてくれたらすぐに支払おう。\n金は一週間後には用意できるが、それより早くは無理だ。だから急がなくてもいいが、あまり遅れないように頼むぜ。";
			link.l1 = "分かりました、旦那。すぐに取りかかります。";
			link.l1.go = "zpq_prs5_ok";
		break;
		
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		
		case "zpq_ex":
			dialog.text = "やっと来たか！もう俺たちの取引のことなんか忘れちまったかと思ったぜ。 すぐに兵士たちにお前の船の荷下ろしを始めさせる。火薬の扱いはとても繊細な仕事だからな、ははっ！";
			link.l1 = "素晴らしいですよ、旦那、でもお支払いを忘れずにお願いします。";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 15000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		
		case "zpq_ex2":
			dialog.text = "はい、もちろんです。約束通り五万ペソをお支払いします。";
			link.l1 = "おい、旦那、冗談じゃねえだろ？！俺たちは10万ペソで取引したはずだぜ！";
			link.l1.go = "zpq_ex3";
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "（信用できる）お前が俺をだまそうとしてるんじゃないかと思い始めたぜ。だから12万5千ペソを受け取るまでは絶対にここを離れねえ！";
				link.l2.go = "zpq_ex4";
			}
			link.l3 = "ふむ……状況が変わったようだな。さて、金をもらって立ち去るとするか……";
			link.l3.go = "zpq_ex5";
		break;
		
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 35)
			{
				Notification_Skill(true, 36, SKILL_LEADERSHIP);
				dialog.text = "ああ、そうだ……まさにその通り！十万ペソだな。すっかり忘れておった、すまんのう。年のせいじゃ、硬化症でな……もちろん、これが約束の金貨じゃ。取引できて楽しかったぞ、船長。さて、すまんが、 わしはまだ仕事が山ほどあるんじゃ……\n";
				link.l1 = "あんたもだよ、旦那。またな。";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
				AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 100000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				Notification_Skill(false, 36, SKILL_LEADERSHIP);
				dialog.text = "「なんだと！？金を持ってさっさと失せろ、さもないとこの独房でくたばることになるぞ！」";
				link.l1 = "お前は本当に嘘つきだな、旦那！素直に俺の金を返すことを勧めるぜ、さもないと積荷を押収するぞ！";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "失礼……よし、あんたの提示した金を受け取って、これで終わりだ。";
				link.l2.go = "zpq_ex5";
			}
		break;
		
		case "zpq_ex4":
				dialog.text = "なんて無礼なんだ！私は正気だし、十万ペソを申し出たのははっきり覚えているぞ。\nくそっ！お前の茶番には付き合わん！";
				link.l1 = "落ち着け。お前の砦の目の前に火薬を満載した火船がいることを考えてみろ。俺が一言でも発したら、 その砦は跡形もなく吹き飛ぶぞ。";
				link.l1.go = "zpq_ex6";
		break;
		
		case "zpq_ex6":
			dialog.text = "ふむふむ……強い主張だな。１２万５千ペソだって？ほら、持っていけ。それじゃ、悪いが俺はこれから仕事があるんだ……";
			link.l1 = "さらばだ、旦那。また会おう。";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "5");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 125000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			/*else
			{
				dialog.text = "「何だと？！俺は軍人だぞ！俺を脅せると思ってるのか、このガキが？！衛兵ども、連れて行け」 "+GetSexPhrase("彼","彼女")+"!";
				link.l1 = "やれるもんならやってみろ、砲台のネズミどもめ……";
				link.l1.go = "zpq_ex_war";
			}*/
		break;
		
		case "zpq_ex5":
			dialog.text = "素晴らしい！いい選択をしたな。コインを受け取って、じゃあな。楽しかったぜ！";
			link.l1 = "さらば……";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 50000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		
		case "zpq_ex_agry":
			dialog.text = "ああ、この野郎！衛兵ども、捕まえろ "+GetSexPhrase("彼","彼女の")+"!";
			link.l1 = "うおおっ！どうやらお前の死体から金をいただくしかなさそうだな……";
			link.l1.go = "zpq_ex_war";
		break;
		
        case "zpq_ex_war":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			pchar.questTemp.zpq = "failed";
            AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 100000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade_21");
			EquipCharacterbyItem(npchar, "blade_21");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass3");
			chrDisableReloadToLocation = true;
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");
			AddSimpleRumour("Such terrible things happen here! They say that some prisoner has escaped from the casemates! He slaughtered all the guards, stole the treasury, and just went away! Shiver me timbers!", SPAIN, 5, 1);
		break;
		// <-- Опасный груз
	}
}

void GetGunType()
{
	int iGunType;
	if(makeint(pchar.rank) < 6) iGunType = rand(1);	//18&&24
	if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 15) iGunType = rand(2); //24&&32	
	if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 24) iGunType = rand(2)+2; //32&&36&&42
	if(makeint(pchar.rank) >= 24) iGunType = 5-rand(1); //36clv&&42
	int iAdd = makeint(GetSummonSkillFromName(pchar, SKILL_COMMERCE)/20);
	
	switch (iGunType)
	{
		case 0:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;     					
			pchar.questTemp.PrisonGun.Price = 28 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "24 calibre cannons";
		break; 
		case 1:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_18;     					
			pchar.questTemp.PrisonGun.Price = 25 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "couleuvrines";
		break; 
		case 2:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;     					
			pchar.questTemp.PrisonGun.Price = 32 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "32 calibre cannons";
		break; 
		case 3:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_36;     					
			pchar.questTemp.PrisonGun.Price = 36 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "36 calibre cannons";
		break;
		case 4:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_36;     					
			pchar.questTemp.PrisonGun.Price = 49 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "full couleuvrines";
		break; 
		case 5:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;     					
			pchar.questTemp.PrisonGun.Price = 40 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+20+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "42 calibre cannons";
		break; 
	}
}
