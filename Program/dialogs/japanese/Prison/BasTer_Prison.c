// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "話せ、聞いてやる。";
			link.l1 = "俺が間違ってた。じゃあな。";
			link.l1.go = "Exit";
			// --> Тичингиту
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
            {
                link.l1 = "インディアンが拘留されている。ファディー・ザ・モスコバイトに捕まったやつだ。そいつと話してもいいか？";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
            {
                link.l1 = "教えてくれ、本当にこのインディアンを絞首刑にするつもりか？\nそんな小さな罪にしては、あまりにも重すぎる罰じゃねえか？";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
            {
                link.l1 = "また俺だ、司令。モスクワ人のファディがこの嘆願書を書いて、インディアンの釈放を求めている。これだ。";
                link.l1.go = "Tichingitu_6";
            }
			// <-- Тичингиту
			//Jason --> Бесчестный конкурент
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "地元の店主の依頼でお前のところに来たんだ、名前は "+pchar.questTemp.Shadowtrader.Tradername+"。彼がこの手紙をあなたに渡してくれと頼んだ。";
				link.l1.go = "Shadowtrader_prison";
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "また俺だ。俺には確かな証拠があるんだが "+pchar.questTemp.Shadowtrader.Tradername+" 正しい。";
				link.l1.go = "Shadowtrader_prison2";
			}
			//Jason <-- Бесчестный конкурент
			//Sinistra --> Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTurma"))
            {
                link.l1 = "ロングウェイという男を探しているんだ。あんたも彼を探していると聞いたぜ、オフィサー旦那。 何か手がかりは掴めたか、それとも見つける目処でも立ったのか？";
                link.l1.go = "PZ_IshemLongway_1";
            }
			//Sinistra <-- Путеводная звезда
		break;
		
		// --> Тичингиту
		case "Tichingitu":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			dialog.text = "ああ、ファディが自分の話をしたのか？俺がお前にあいつを見せるのを止める理由はねえよ、旦那。 あの赤肌を見に来たのはお前が初めてじゃねえ。まあ、十日もすりゃあ、あいつを太陽の下に吊るして干すから、 町の連中みんなが見物できるさ…";
			link.l1 = "それで、俺は牢屋に入ってもいいのか？";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "もう言っただろ、「それを禁じる理由は俺にはねえ」。さっさと行け。";
			link.l1 = "ありがとう！";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			DelLandQuestMark(npchar);
			dialog.text = "お前はここに来たばかりだな、旦那？ヨーロッパから来たばかりか？植民地の事情なんて分かっちゃいないだろう。 この処刑は、フランス植民者の財産に手を出すあのインディアン野郎どもへの見せしめになるのさ。\nそれに、ファディ自身が強く望んでいるし、あいつはこの地でとても尊敬されている男だ。 うちの総督とも親しい友人なんだぜ。";
			link.l1 = "罰を軽くする方法はないのか？俺はまだ、それが厳しすぎると思ってるんだが…";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "ああ、説教は勘弁してくれ！本当にそのインディアンの運命が気になるなら、 ファディのところへ行って本人について聞いてこい。ファディが釈放の嘆願書を書けば、俺たちはそれを認めてやる。";
			link.l1 = "了解だ、役人。ファディーのところへ行くぜ。";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "fadey";
			AddLandQuestMark(characterFromId("fadey"), "questmarkmain");
			QuestPointerToLoc("BasTer_town", "reload", "houseSp1");
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "（読み上げながら）ふむ……このファデイって奴は妙だな……公開処刑を要求しておいて、今度はこのインディアンを釈放しろだと……まあ、総督の友人なんてみんなこんなもんか。いいだろう、行け、この赤肌を連れていけ。";
			link.l1 = "感謝するぜ、役人！";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			AddQuestRecord("Tichingitu", "3");
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- Тичингиту
		
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_prison":
			dialog.text = "「またそれか」 "+pchar.questTemp.Shadowtrader.Tradername+" あいつの文句か！よし、今回は何だ……（書類を読む）";
			link.l1 = "...";
			link.l1.go = "Shadowtrader_prison_1";
			RemoveItems(PChar, "letter_1", 1);
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison_1":
			dialog.text = "またしても、馬鹿げた憶測ばかりで、決定的な証拠は一つもないじゃねえか！\nよし。あいつに伝えろ――これだけじゃ俺が衛兵に警戒を命じて町中を捜索させるには全然足りねえってな。";
			link.l1 = "俺にそれをあいつに伝えろってのか？";
			link.l1.go = "Shadowtrader_prison_2";
		break;
		
		case "Shadowtrader_prison_2":
			dialog.text = "その通り――できれば一字一句そのまま伝えてくれ。あいつなら俺の言いたいことが分かるはずだ。 こんな厄介な奴のために返事を書く紙を無駄にする気はねえ。";
			link.l1 = "なるほど。では、さらばだ。";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.Trouble = "true";
			NextDiag.TempNode = "First_officer";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "Shadowtrader_prison2":
			dialog.text = "「それで、お前が集めたと言う『確かな』証拠ってのは何だ？」";
			link.l1 = "俺は密輸業者と、あいつらの非公式な店を通じて品物を買う取引をしたんだ。今夜、あいつらの手先が港の役所に来て、 例の「店」とやらに案内してくれるらしい。";
			link.l1.go = "Shadowtrader_prison2_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
			pchar.quest.Shadowtrader_SMG.over = "yes";//снять оба прерывания
			sld = characterFromID("ShadowAgent_1");
			sld.lifeday = 0;
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison2_1":
			dialog.text = "ふむ……よくやったな、船長！これで次の段階に進める。うちの者をあいつらの集会に送り込んで、隠れ家を突き止め、 全員を逮捕するつもりだ。積極的な働きに感謝するぞ！";
			link.l1 = "いつでも力になるぜ。お前の作戦がきっとうまくいくと信じてる。";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.End.Fort = "true";
			AddQuestRecord("Shadowtrader", "7");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			SetTimerFunction("ShadowTrader_questmark", 0, 0, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			NextDiag.TempNode = "First_officer";
		break;
		// <-- мини-квест Бесчестный конкурент
		
		// Sinistra - Квест "Путеводная звезда" ==>
		case "PZ_IshemLongway_1":
			DelLandQuestMark(npchar);
			dialog.text = "誰だ？ロング…ウェイ？最近この町にイングランド人が来た覚えはねえな。";
			link.l1 = "いや、ロングウェイは……中国人だ。";
			link.l1.go = "PZ_IshemLongway_2";
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
			DeleteQuestCondition("PZ_BasTerPeshera");
		break;
		
		case "PZ_IshemLongway_2":
			dialog.text = "ほうほう。それで、あんたのそのロングウェイを何のために探しているんだ、旦那？";
			link.l1 = "あいつは俺の友人だ。何があったかはもう聞いている――悲しい誤解だと俺は保証するぜ。";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "あいつを探しているのは、この諸島で悪名高い犯罪者だからだ。";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_IshemLongway_Zashita_1":
			dialog.text = "ああ、誤解だ。俺たちは現場であいつを更生させようとしたわけじゃねえ。まずは話をしたかっただけだ……とりあえずな。だがな、お前のその凶暴な黄色い野郎は、街の衛兵を何人も斬り捨てただけじゃなく、 追跡のためにジャングルへ送った部隊まで皆殺しにしやがったんだ。";
			link.l1 = "また部隊を送るつもりか？俺があんたの部下と一緒に行って、あいつと話して落ち着かせて、 もう一度惨事が起きるのを防ぐこともできるぜ。\n殺しが止まってロングウェイが街から永久に出て行けば、それで十分か？";
			link.l1.go = "PZ_IshemLongway_Zashita_2";
		break;
		
		case "PZ_IshemLongway_Zashita_2":
			dialog.text = "通常ならお前に同意するかもしれん。だがな、殺された者の中に士官がいたんだ――将来有望な若い中尉で、閣下のお気に入りだった。町中が喪に服している。見て見ぬふりも、帳消しもできねえんだ。 わかるだろう？";
			link.l1 = "よく分かりました。友人の行動についてお詫びします。これ以上ご迷惑はおかけしません。";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
			link.l2 = "なあ、ジャングルで何が起きてるかなんて神様しか知らねえよ。あの連中を殺したのは誰だっておかしくねえ。";
			link.l2.go = "PZ_IshemLongway_Blef_1";
		break;
		
		case "PZ_IshemLongway_Blef_1":
			dialog.text = "「それで、誰が士官に率いられた巡回隊全員を倒せたと思ってるんだ？」";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "（信用できる）盗賊だよ、他に誰がいる？恥ずかしい話だが、最近でかい一味からかろうじて逃げ延びたんだ。";
				link.l1.go = "PZ_IshemLongway_Blef_2";
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "だが、俺にわかるわけねえだろう？誰だってありえるさ――盗賊か、海賊か、間者かもしれねえ…";
				link.l1.go = "PZ_IshemLongway_Blef_netVD_1";
			}
		break;
		
		case "PZ_IshemLongway_Blef_2":
			dialog.text = "へっ、まあ当然だな――お前の体格を見りゃな、船長。ああ、最近この島にはそんな悪党どもがうろついてやがるんだ…";
			link.l1 = "その通りだ！つまり、あいつらが哨戒隊と哀れな少尉を皆殺しにしたってことか。";
			link.l1.go = "PZ_IshemLongway_Blef_3";
		break;
		
		case "PZ_IshemLongway_Blef_3":
			dialog.text = "残念ながら、それは十分あり得ることだ。";
			link.l1 = "その通りだ。だからもう一度頼む、次の捜索隊に俺を加えてくれ――ロングウェイは俺の言うことを聞くし、そうすればこれ以上の犠牲を避けられるんだ。";
			link.l1.go = "PZ_IshemLongway_Blef_4";
		break;
		
		case "PZ_IshemLongway_Blef_4":
			dialog.text = "わかった。しかし、まだ一つ「だが」があるんだ、旦那。";
			link.l1 = "「それは何だ？」";
			link.l1.go = "PZ_IshemLongway_Blef_5";
		break;
		
		case "PZ_IshemLongway_Blef_5":
			dialog.text = "ジャングルで起きたこととは違い、お前の仲間の都市での罪は明白で完全に証明されている。罰を逃れることはできん。 だから、もし奴を生きてこの街から出したいなら、この死の償いをしなければならん。";
			link.l1 = "なるほどな。いくらかかるんだ、旦那役人？";
			link.l1.go = "PZ_IshemLongway_Blef_6";
		break;
		
		case "PZ_IshemLongway_Blef_6":
			dialog.text = "三百ドゥブロンだ。その金は市場の口論屋どもじゃなく、ちゃんと街に入るぞ。";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "もちろんだ。三百ドゥブロンだ――ほらよ。";
				link.l1.go = "PZ_IshemLongway_Blef_7";
			}
			link.l2 = "今回は町にドゥブロンを持ってきてねえんだ。だが、もし取りに行かせてくれるなら……";
			link.l2.go = "PZ_IshemLongway_NetDublonov_1";
		break;
		
		case "PZ_IshemLongway_Blef_7":
			dialog.text = "素晴らしい。お前の責任感は証明されたな。次の部隊への説明を最終確認しているところだ。お前に参加を許可する。";
			link.l1 = "ありがとうございます。さようなら、オフィサー旦那。";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.PZ_DrugOtryad = true;
		break;
		
		case "PZ_IshemLongway_NetDublonov_1":
			dialog.text = "俺は昨日今日生まれたわけじゃねえ。お前が逃げ出すつもりだってことは分かってる――ドゥブロン金のためじゃなく、大事なあの中国人のためにな。";
			link.l1 = "俺はロングウェイと一緒に町を出たりしねえと誓うぜ。";
			link.l1.go = "PZ_IshemLongway_NetDublonov_2";
		break;
		
		case "PZ_IshemLongway_NetDublonov_2":
			dialog.text = "言葉ばかりだな……もうお前のくだらねえおしゃべりにはうんざりだ、船長。俺たちがこの忌々しい黄色い肌の男を自分で捕まえるまで、 お前はどこにも行かせねえぞ。";
			link.l1 = "その場でロングウェイを殺さないと約束してくれるなら、旦那、あんたの命令に従うぜ。";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "「だが、俺自身が今日この街の法を破ったか？」";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_1":
			dialog.text = "なら知らねえってことだな。俺は今の勘を信じるぜ――あの中国野郎はどうあっても捕まえなきゃならねえ。";
			link.l1 = "今の勘か？だが、ロングウェイがジャングルで全員を殺したという証拠はないだろう。";
			link.l1.go = "PZ_IshemLongway_Blef_netVD_2";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_2":
			dialog.text = "それで、あいつの無実を証明するものがあるのか？ないんだな？だったら、その黄色い肌の男を聖人扱いするのはやめろ。 わかったか？";
			link.l1 = "よく分かりました。友人の行動についてお詫びします。これ以上ご迷惑はおかけしません。";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
		break;
		
		case "PZ_IshemLongway_Uiti_1":
			dialog.text = "残念だが、まだ帰すわけにはいかんぞ、船長。";
			link.l1 = "どういう意味だ？";
			link.l1.go = "PZ_IshemLongway_Uiti_2";
		break;
		
		case "PZ_IshemLongway_Uiti_2":
			dialog.text = "つまりだな、このロングウェイって野郎があんたの友達なら、あんたが後を追って一緒に逃げる可能性があるってことだ。 \nだからよ、俺たちがこの黄色い肌の殺し屋を自分で捕まえるまで、あんたをここに留めておくしかねえんだ。";
			link.l1 = "その場でロングウェイを殺さないと約束してくれるなら、旦那、あんたの命令に従うぜ。";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "「だが、俺自身が今日この街の法を破ったか？」";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Arest_1":
			dialog.text = "何も約束はできねえぜ。お前の仲間が何を考えてるかなんて分からねえし、 俺たちの姿を見たらまた暴れ出すかもしれねえからな。\nその間は、豪華な牢屋生活を楽しんでくれよ、船長。";
			link.l1 = "おかしいな……";
			link.l1.go = "PZ_IshemLongway_Arest_2";
		break;
		
		case "PZ_IshemLongway_Arest_2":
			DialogExit();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto9", "PZ_SharliePlennik_BadFinal");
		break;
		
		case "PZ_IshemLongway_Pobeg_1":
			dialog.text = "誤解しないでくれ、俺はお前個人に恨みはねえんだ。それに、お前の言う通り、何も罪は犯していない。だがな、 お前の黄色い肌の友人が法の裁きを逃さないようにしなきゃならねえんだ。";
			link.l1 = "ならば、こんな茶番で俺を拘束させるつもりはねえってことを理解しろ。";
			link.l1.go = "PZ_IshemLongway_Pobeg_2";
		break;
		
		case "PZ_IshemLongway_Pobeg_2":
			if (pchar.location.from_sea == "BasTer_Town")
			{
				dialog.text = "その場合は、おとなしくしてもらうぞ、旦那。";
			}
			else
			{
				dialog.text = "もう我慢ならん！軍曹、部隊をあの忌々しい洞窟へ連れて行き、中国人を見つけてこい！こいつは俺が直々に片付ける……";
			}
			link.l1 = "そんなことさせるかよ。";
			link.l1.go = "PZ_IshemLongway_Pobeg_3";
		break;
		
		case "PZ_IshemLongway_Pobeg_3":
			DialogExit();
			
			LAi_SetHuberType(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_MoveCharacter(NPChar, "FRANCE_CITIZENS");
			LAi_group_Attack(characterFromId("BasTer_Mayor"), Pchar);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			if (pchar.location.from_sea == "BasTer_Town")
			{
				PChar.quest.PZ_KorablPort_BadFinal.win_condition.l1 = "MapEnter";
				PChar.quest.PZ_KorablPort_BadFinal.win_condition = "PZ_KorablPort_BadFinal";
				AddQuestRecord("PZ", "10");
				LocatorReloadEnterDisable("BasTer_town", "gate_back", true);
				Island_SetReloadEnableGlobal("Guadeloupe", false);
			}
			else
			{
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition.l1 = "EnterToSea";
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition = "PZ_KorablBuhta_BadFinal";
				AddQuestRecord("PZ", "5");
				
				// Микро-диалог с Лонгвэем у пещеры, если мы побежали к пещере ему помочь после ссоры с комендантом
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1 = "location";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1.location = "Guadeloupe_CaveEntrance";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition = "PZ_IshemLongway_SorraKomendant";
				
				LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
				LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
				//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			}
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_1":
			dialog.text = "賞金稼ぎか。普段ならお前らみたいな連中とは関わりたくねえが、今回は利害が一致してるからな。 どうやらこの黄色い肌の奴は悪名高い殺し屋らしい。町でもジャングルでも俺の部下を何人も殺してきたんだ。";
			link.l1 = "俺はもうしばらくの間、あいつを諸島中追い回してるんだ。";
			link.l1.go = "PZ_IshemLongway_OhotnikOtryad_2";
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_2":
			dialog.text = "くそったれめ！こうするぞ：俺がもう一隊集める、お前はそいつらと一緒に行け。今度はあいつに逃げ場はねえし、 お前の協力があれば成功の可能性も上がるだろう。ただし、俺から報酬は期待するな――お前は賞金稼ぎなんだから、雇い主から金をもらえ。俺と協力させてやるだけでもありがたく思えよ。";
			link.l1 = "確かにその通りだな。じゃあな、役人。またあの中国人とやり合ってお前の部下が生き残ったら、 どうなったか教えてやるぜ。";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			pchar.questTemp.PZ_OhotnikOtryad = true;
		break;
		
		case "PZ_IshemLongway_BeryomOtryad":
			DialogExit();
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			DoQuestReloadToLocation("Guadeloupe_jungle_02", "goto", "goto1", "PZ_IshemLongway_Otryad");
		break;
		
		case "PZ_BasTer_ComendantDialog_1":
			dialog.text = "あんたの言う通りだ。二人は知り合いなんだな？お互いどういう関係なんだ？";
			link.l1 = " 奴は俺の船の航海士で、そして…";
			link.l1.go = "PZ_BasTer_ComendantDialog_2";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "あいつを探しているのは、諸島で悪名高い犯罪者だからだ。";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_BasTer_ComendantDialog_2":
			dialog.text = "あいつは地図よりも銃の扱いの方が得意だ。お前の飼ってる中国人が何をしでかしたか、分かってるのか？";
			link.l1 = "正直に言うと、いや、俺は今さっき入港して探し始めたばかりなんだ。全部誤解だったに違いねえよ。";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_1":
			dialog.text = "その通りだ。お前はあいつにとって何者なんだ、そこまで欲しがるとは？\nまあ、そんなことはどうでもいい――大事なのはお前がこの街に来た目的だ。";
			link.l1 = "違法なことは何もありません、旦那。ですが、「もう関係ない」とはどういう意味ですか？彼は……";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_2";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_2":
			dialog.text = "ああ。やつは墓地から少し離れた丘の裏に埋葬されたんだ。\n聖職者たちは異教徒にきちんとしたキリスト教式の埋葬を許さなかったのさ。";
			link.l1 = "もし差し支えなければ、どうしてそんなことになったんだ？";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_3";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_3":
			dialog.text = "簡単な話だ――あいつは街に来て、しつこく嗅ぎ回っていた。俺たちは何をしているのか聞き出そうとしたが、 あいつは何人か殺してジャングルに逃げ込んだ。俺は次々と捜索隊を送り込んだが、全部返り討ちにされた！ 仕方なく洞窟に追い込んで、あとは射手たちが片をつけたんだ。";
			link.l1 = "それで、あいつが何を探していたのか分からねえのか？見ての通り、こんなことは初めてだったんだ――もともと俺の船の航海士だったんだぜ。だが、そいつは俺から盗みを働いて逃げやがったんだ。";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_4";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_4":
			dialog.text = "うっかり忘れてたぜ、ああ。お前もあいつのせいで痛い目を見たのか？いい教訓になっただろう、船長。 信用できねえ奴を雇うもんじゃねえって、これで分かったはずだ。黄色い肌の奴は絶対に信用するな――俺の言葉を覚えとけよ！";
			link.l1 = "ああ、そのことは覚えておくぜ。奴について何か分かったか？";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_5";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_5":
			dialog.text = "おお、盗まれた品を取り戻したいのか？あいつのポケットには銀貨が少し入ってたが、もしお前から盗んだものなら、 もう全部使っちまってるぜ。あと、他にも何枚か書類があったな…お前の船の航海日誌か？どうせ俺たちには意味が分からなかったが――暗号か何かか？全部血まみれで、無事な部分は判別できなかったぜ。";
			link.l1 = "え、はい。ありがとうございます。自分の日記や記録帳が他人に拾われたらどうなるか、ずっと心配していたんです……";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_6";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_6":
			dialog.text = "「それで、わざわざ複雑な暗号まで考えなきゃならなかったのか？ 自分の時間と労力がもったいないと思わなかったのかよ？ほら、これだ。\nそれと銀の件だが……怒るなよ、街に返したんだ。あの中国野郎のせいで、あの日は俺の部下が何人も死んだからな。」";
			link.l1 = "それなら、無理には言わねえ。じゃあな。";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_7";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_7":
			DialogExit();
			
			LAi_SetHuberType(npchar);
			AddQuestRecord("PZ", "9");
			CloseQuestHeader("PZ");
			bDisableLandEncounters = false;
		break;
		// <== Квест "Путеводная звезда" - Sinistra
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
