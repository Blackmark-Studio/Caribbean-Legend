// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","「どうなさいましたか、」 "+GetAddress_Form(NPChar)+"?"),"「少し前に俺に質問しようとしたよな、」 "+GetAddress_Form(NPChar)+"...","今日一日で、これで三度目だぜ、お前が何か質問を持ち出すのは……","また質問かい？","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わったんだ……","今は話すことは何もねえぜ。"),"うーん、俺の記憶はどこに行っちまったんだ…","「ああ、本当にこれで三度目だな……」","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Jason, Бремя гасконца
			if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
			{
				link.l1 = "旦那、仕事を探してるんだ。何か用はあるか？";
                link.l1.go = "Sharlie_rum";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
			{
				link.l1 = "任務は果たしたぜ。ラム酒を積んだロングボートはル・フランソワ湾に届けて、お前さんの仲間に引き渡した。";
                link.l1.go = "Sharlie_rum_5";
			}	
			//<-- Бремя гасконца */
			
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
			{
				link.l1 = "お前の部屋を二、三日借りたいんだ。俺の船にケガ人がいてな。そいつに休ませて回復させてやらなきゃならねえんだ。";
				link.l1.go = "Portugal";
			}
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
			{
				link.l1 = "教えてくれ、俺が部屋を借りてやった友人はもう出て行ったのか？待ってると約束してたのに、部屋は空っぽなんだ。";
				link.l1.go = "Portugal_2";
			}
			//Португалец
			// Jason Долго и счастливо
			if (!CheckAttribute(npchar, "quest.LongHappy") && CheckAttribute(PChar, "questTemp.LongHappy.MarryRum") && LongHappy_CheckTavernGoods())
			{
				link.l1 = "俺の部下たちのために宴を開くつもりだ。もう知ってるんじゃねえか？";
				link.l1.go = "LH_tavern_SP";
			}
			if (CheckAttribute(npchar, "quest.LongHappy.Nomoney") && LongHappy_CheckTavernGoods() && sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "祝いのために必要なものは全部持ってきたぜ。";
				link.l1.go = "LH_tavern_SP_3";
			}
		break;
		
		//--> Jason, Бремя гасконца
		case "Sharlie_rum":
			DelLandQuestMark(npchar);
			dialog.text = "任務か？ふむ……お前、なかなか頭が回りそうだな、坊主。ちょうど頼みたいことがあるかもしれねえ\nこの仕事は簡単そうに聞こえるが、責任感と知恵が必要だ。あいつらみたいな間抜けには任せられねえ、 絶対に台無しにされちまうからな……";
			link.l1 = "聞いてくれ、俺に何を任せたいのか、はっきり教えてくれないか？絶対に期待は裏切らねえ、いや、 少なくとも全力は尽くすぜ。";
			link.l1.go = "Sharlie_rum_1";
		break;
		
		case "Sharlie_rum_1":
			switch(rand(4))
			{
				case 0:
					pchar.questTemp.Sharlie.Rum.Pass = "Old Thomas has grown tired of waiting for the beer";
				break;
				case 1:
					pchar.questTemp.Sharlie.Rum.Pass = "The boards and the oakum will be here in the morning";
				break;
				case 2:
					pchar.questTemp.Sharlie.Rum.Pass = "Don't wait for the south wind";
				break;
				case 3:
					pchar.questTemp.Sharlie.Rum.Pass = "The bay is ready for disembarkation";
				break;
				case 4:
					pchar.questTemp.Sharlie.Rum.Pass = "The camels are going north";
				break;
			}
			dialog.text = "よし。俺の酒場に上等なジャマイカ産ラム酒の樽をいくつか運んでくれる奴が必要なんだ。だがな、 輸入関税が儲けを削るし、常連の連中は喉が渇いてる。だから税関役人に見つからないように賢く動かねえとな。 ラガー船『ゴースト』が今夜マルティニーク沖に来るぜ\nラマンタン湾の近くに錨を下ろすはずだ。その船を見つけて乗り込め。 俺がお前にロングボートと水夫を五人用意してやる、そいつらはお前の命令に従う\n船に乗ったら、男が近づいてくる。その時合言葉を伝えなきゃならねえ：「"+pchar.questTemp.Sharlie.Rum.Pass+"'\n答えは「ラムでもどうだい、水夫？」だぜ。一度きりのチャンスだから、しっかり書き留めて間違えるなよ、 しくじったら取引はなしだ。だからこそ、お前と一緒に航海する脳みその足りねえ連中には任せられねえんだ。 合言葉を繰り返してみろ。";
			link.l1 = "「」"+pchar.questTemp.Sharlie.Rum.Pass+"「。」";
			link.l1.go = "Sharlie_rum_2";
		break;
		
		case "Sharlie_rum_2":
			dialog.text = "よし。もう何度か自分で繰り返すか、できればどこかに書き留めておけ。合言葉をラガー船の船長に伝えたら、 ラム酒の箱がロングボートに積み込まれる。そのロングボートで海賊の集落ル・フランソワの湾まで運べばいい――そこで歓迎されるだろう。\nそれが全ての任務だ。ル・フランソワ湾からサン・ピエールまでは徒歩で行ける。ロングボートは湾に残しておけ。 終わったら五千エイト銀貨を払うぜ。";
			link.l1 = "密輸か、面白そうだし儲かりそうだな。言われた通りにするぜ。\n長艇はどこだ？";
			link.l1.go = "Sharlie_rum_3";
			link.l2 = "つまり、俺に密輸をやれって提案か？ふむ……だがな、俺の名を危険にさらすわけにはいかねえんだ。悪いが、何も聞かなかったことにしてくれよ。";
			link.l2.go = "Sharlie_rum_exit";
		break;
		
		case "Sharlie_rum_exit":
			dialog.text = "かしこまりました、旦那。ほかに仕事はありません。";
			link.l1 = "なるほど。じゃあ、幸運を祈るぜ。 "+npchar.name+".";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
		break;
		
		case "Sharlie_rum_3":
			dialog.text = "ロングボートは夕方七時に桟橋にいるぜ。ロングボートの乗組員は腕がいいから、すぐにラガー船にたどり着けるはずだ。 全部で四時間もかからねえだろう――きっと夜十一時にはサン・ピエールに戻れるぜ。これを持っていけ、望遠鏡だ。ガラクタだが、ないよりマシだろ。 ラマンテン・ビーチは島の北側にあるから、港を出たら真北に進路を取れ。幸運を祈るぜ！";
			link.l1 = "わかったぜ。またすぐ会おうな。 "+npchar.name+"!";
			link.l1.go = "Sharlie_rum_4";
		break;
		
		case "Sharlie_rum_4":
			DialogExit();
			AddQuestRecord("SharlieB", "1");
			AddQuestUserData("SharlieB", "sPassword", pchar.questTemp.Sharlie.Rum.Pass);
			GiveItem2Character(pchar, "spyglass1"); 
			Log_Info("You've received a spyglass");
			PlaySound("interface\important_item.wav");
			if(CheckAttribute(pchar, "questTemp.Sharlie.FastStart"))
			{
				GiveItem2Character(pchar, "map_martiniqua");
				Log_Info("You have received a map of Martinique");
				RefreshEquippedMaps(GetMainCharacter());
			}
			/* pchar.quest.Sharlie_rum.win_condition.l1 = "location";
			pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town"; */
			//pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
			//pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
			pchar.quest.Sharlie_rum.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_rum.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
			SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
			pchar.questTemp.Sharlie.Rum = "true";
			npchar.quest.Rum = "true";
			NewGameTip("Open your inventory (F1) and equip the spyglass.");
			pchar.quest.NgtBarkas.win_condition.l1 = "location";
			pchar.quest.NgtBarkas.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.NgtBarkas.win_condition.l2 = "HardHour";
			pchar.quest.NgtBarkas.win_condition.l2.hour = 19.00;
			pchar.quest.NgtBarkas.function = "NgtBarkas";
			AddTimeToCurrent(1,30);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			QuestPointerToLoc("fortfrance_town", "reload", "reload1_back");
		break;
		
		case "Sharlie_rum_5":
			dialog.text = "素晴らしい！お前なら頼りになると思ってたぜ。大変だったか？";
			link.l1 = "「そうだな、それは“きつい”をどう定義するかによるぜ…」";
			link.l1.go = "Sharlie_rum_6";
		break;
		
		case "Sharlie_rum_6":
			dialog.text = "さて、これが報酬だ。五千ペソだぜ。望遠鏡はそのまま持ってていい。さらにもう一つ、小さな贈り物だ――このラム酒三本を受け取ってくれ。\n一口飲めば、なぜこんなに人気があるのかすぐに分かるはずさ。";
			link.l1 = "ありがとう！一緒に仕事ができて楽しかったぜ！また会おうな！";
			link.l1.go = "Sharlie_rum_7";
		break;
		
		case "Sharlie_rum_7":
			DialogExit();
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "potionrum", 3);
			AddQuestRecord("SharlieB", "5");
			CloseQuestHeader("SharlieB");
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			DelLandQuestMark(npchar);
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		//<-- Бремя гасконца
		
		//Португалец
		case "Portugal":
			dialog.text = "問題ねえ、部屋はあるぜ。50ペソで三日間使えるぞ。";
			if (sti(pchar.money) >= 50)
			{
				link.l1 = "「ほら、どうぞ。」";
				link.l1.go = "Portugal_1";
			}
			else
			{
				link.l1 = "財務官から金を取ってきて、すぐ戻るぜ。";
				link.l1.go = "exit";
			}
		break;
		
		case "Portugal_1":
			ref sld;
			DialogExit();
			AddMoneyToCharacter(pchar, -50);
			npchar.quest.Portugal = "true";
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
			pchar.quest.Portugal_Ill3.over = "yes";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true);//закрыть выходы из города
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
			sld = characterFromId("PortugalDoctor");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
			pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
			pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
			pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
		break;
		
		case "Portugal_2":
			dialog.text = "自分で立ち上がって部屋を出ていったとは言えませんな、旦那。昨日ここに何人か来たんですよ。その中に、 背が高くて痩せこけた片目の男がいて――見た目からして明らかに盗賊でしたよ。それに、舌足らずな男もいて、カスティーリャ人のようでした。驚きましたが、 その舌足らずの男が俺を睨んできて……まるでシラミを潰す前に見るような目つきでね。で、あんたの友達のことを聞かれて……俺は話しましたよ。他にどうしろって言うんです？";
			link.l1 = "知ってるぜ "+npchar.name+"「お前は英雄じゃねえな、その通りだ。で、他に何を見た？奴らはどこへ行ったんだ？」";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "それだけだ……いや、待てよ！そうだ、一つ目の男が馬車のことを言ってたな。たぶん奴らは馬車を使って、 お前の仲間を島の反対側まで引きずっていったんだろう。それで全部だ、旦那、誓うぜ……衛兵を呼びたいところだが、あの舌足らずの野郎、出ていく前に俺の女房が美人だなんて言いやがって……わかるだろ？もし俺が全部話したってバレたら、奴らに……\n";
			if (pchar.money >= 1000)
			{
				link.l1 = "怖がるな、俺からは弾丸以外何も聞かれやしねえよ。お前には本当に助けられた、ありがとうな。ほら、礼として1000ペソ受け取れ。";
				link.l1.go = "Portugal_4";
			}
			link.l2 = "大したことじゃねえが、とにかく礼は言っとくぜ。次は衛兵を呼んで、そんな腰抜けみてえな真似はやめろよ。";
			link.l2.go = "Portugal_5";
		break;
		
		case "Portugal_4":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "ありがとうございます、旦那。あなたのご友人はほとんど回復されたとお約束できます。 少なくとも自分の足で歩いていましたよ。それから、あの静かなオランダ人の男がちょうどその時外から入ってきて、 その騒ぎを見てすぐに外へ飛び出していきました、跡形もなく消えてしまいましたよ。";
			link.l1 = "あいつはもう見つけた最初の船で出発しちまったんじゃねえかと思うぜ。情報ありがとな、そろそろ俺も行く時間だ。";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_5":
			dialog.text = "「誰もが剣を抜いて英雄になれるわけじゃねえぜ、船長。」";
			link.l1 = "「まあ……それはあいつの選択だぜ。」";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_seapatrol_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//Португалец
		
		// Jason Долго и счастливо
		case "LH_tavern_SP":
			npchar.quest.LongHappy = "true";
			dialog.text = "ああ、あんたの助手が来たが、彼女にも言ったし、あんたにも繰り返すぜ――俺は酔っ払い水夫の群れには慣れてるが、あんたらの宴会がどうなるかも知ってる。 残るのはスペインのテルシオが来た後のアントワープみたいな有様だろうよ。壁が残ってりゃ上出来だ。だからな、 大乱闘をやりたいなら、すでに持ってきた分に加えて返金不可の保証金が必要だぜ。何かあった時のためにな。\n";
			link.l1 = "このずる賢い野郎め！俺は何年も海の荒くれどもと酒を飲んできたし、いろんな…店にも出入りしてきた。持ってきた金があれば、お前の酒場なんざ一から建て直せるってのは分かってるんだぜ！ この状況につけ込んでるんじゃねえのか？まあいい、俺はこれから結婚式に出なきゃならねえし、 こんな些細なことで悩んでる暇はねえ――いくら欲しいんだ？";
			link.l1.go = "LH_tavern_SP_1";
		break;
		
		case "LH_tavern_SP_1":
			dialog.text = "もう10万枚のエイトがあれば十分だぜ、心配すんな――俺が最高のやり方で全部やってやるよ。お前の連中はこの宴を長く忘れられねえだろうさ、覚えておきな！";
			if (sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "ちゃんと気合い入れてくれよ――今日は特別な日なんだ、わかるだろう。\nそれと、宴が終わった後は、たとえお前の酒場が燃えちまっても文句を言いに来るんじゃねえぞ。";
				link.l1.go = "LH_tavern_SP_4";
			}
			else
			{
				link.l1 = "まるで王様の結婚式を仕切ってる気分だぜ！待ってろ、すぐ戻るからな。";
				link.l1.go = "LH_tavern_SP_2";
			}
		break;
		
		case "LH_tavern_SP_2":
			DialogExit();
			npchar.quest.LongHappy.Nomoney = "true";
		break;
		
		case "LH_tavern_SP_3":
			dialog.text = "この宴はお前の連中の記憶に長く残るぜ、俺の言葉を覚えておけよ！";
			link.l1 = "ちゃんと頑張れよ、今日は特別な日なんだぜ、分かるだろ。\nもし俺の連中がうっかりお前の酒場を燃やしちまっても、泣きついてくるんじゃねえぞ。";
			link.l1.go = "LH_tavern_SP_4";
		break;
		
		case "LH_tavern_SP_4":
			DialogExit();
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.questTemp.LongHappy.MarryRum));
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LongHappy.MarryMoney));
			AddMoneyToCharacter(pchar, -100000);
			DeleteAttribute(npchar, "quest.LongHappy.Nomoney");
			pchar.questTemp.LongHappy.DrinkReady = "true";
			pchar.questTemp.LongHappy.MarrySP = "true";
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryMoney");
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryRum");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
