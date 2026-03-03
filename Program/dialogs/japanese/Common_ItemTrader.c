#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
void ProcessDialogEvent()
{
 	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
			
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================	   
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
  		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

  		case "First time":
			dialog.text = NPCharSexPhrase(npchar,"船長、ご自身や士官たちのために装備をお求めですか？もしそうなら、まさに私がうってつけの人物ですよ！","ああ、船長、あなたが私のところに来てくれると分かっていました！あなたや士官たちのための装備、 他にも役立つ品をたくさんご用意できますよ。");
			link.l1 = "何を持っているか見せてみろ。";
			link.l1.go = "Trade_exit";
			
   			/*link.l2 = "俺は別の用事で来たんだ。";
			link.l2.go = "quests";*/
			// --> Мангароса
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "find" && npchar.Merchant.type == "potion" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l4 = "おい、近くで面白い植物を見つけたんだ。\nこれが薬や煎じ薬に使えるかどうか教えてくれないか？\nなんとなく気になってさ。ちょっと見てくれないか？";
				link.l4.go = "mangarosa";
			}
			// <-- Мангароса
			

			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "なあ、上等なヨーロッパ産のワインを一本売ってくれないか？";
				link.l4.go = "Wine_ItemTrader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.bottles") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "聞けよ、お前がヨーロッパのワインを売ってるのは知ってるんだ。六十本必要だ。";
				link.l4.go = "Wine_Bottles";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat1") && NPChar.location == pchar.questTemp.Wine.City + "_town" && npchar.id == pchar.questTemp.Wine.ItemTraderID && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "また俺だ。これって一体どういうことなんだ、ん？";
				link.l4.go = "Wine_Repeat1";
			}
			// <-- мини-квест Дефицитный товар
			
			//Sinistra --> мини-квест "Знакомство с индейцами"
			if (CheckAttribute(pchar, "questTemp.ZsI_PokupaemPistolety") && npchar.Merchant.type == "armourer")
			{
   				link.l4 = "二丁のピストルと、二十発分の弾と火薬が必要だ。";
				link.l4.go = "ZsI_PokupaemPistolety";
			}
			// <-- мини-квест "Знакомство с индейцами"
			
			// --> Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l4 = "聞けよ、「フアン」って名前に心当たりはあるか？";
				link.l4.go = "Consumption";
			}
			// <-- Цена чахотки
			
			//--> Украденное воспоминание
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "旦那、私は並の品ではなく、格別な品質のものを探しているのです。 大多数を満足させるようなありふれた装飾品ではなく、本物の洗練を感じさせる品――例えば、精巧に作られたイヤリングの一対や、貴族の趣味にもふさわしい上品なペンダントなどがよいでしょう。 由緒ある家柄のご令嬢にも喜ばれる贈り物が必要なのです。";
				link.l4.go = "UV_Lavochniki_1";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_2") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "あなたの在庫の中に、何か特別に価値のある品はありませんか？\n最も気難しい貴婦人の趣味さえも満足させるような、普通の市民には到底及ばない、 際立って洗練された一品を探しているのです。\n例えば、珍しい芸術性を持つペンダントや、上品なデザインのブレスレットなどはありませんか？";
				link.l4.go = "UV_Lavochniki_2";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_3") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "教えてくれ、商人殿、高級な宝飾品について詳しいか？私は上流のご婦人に贈る、特別な品を探しているのだ。 率直に言おう、ありふれた安物には興味がない。本当に素晴らしい逸品が欲しい――例えば宝石をあしらったブローチや、比類なき職人技の指輪などだ。";
				link.l4.go = "UV_Lavochniki_3";
			}
			//<-- Украденное воспоминание
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l5 = "聞けよ、お前はいろんな品を扱ってるだろう……昨日か今日、誰かが売りに来たやつはいなかったか\n  "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l5.go = "Device_ItemTrader";
			}
			//<-- генератор Неудачливый вор

			link.l9 = "ありがとうございますが、興味はありません。";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar, 0);
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_ItemTrader":
			dialog.text = "ああ。一本につき七百ペソだ。";
			if (makeint(Pchar.money) >= 700)
			{
				link.l1 = "素晴らしい。金を受け取って、それを俺に渡せ。";
				link.l1.go = "Wine_ItemTrader_1";
			}
			link.l2 = "素晴らしい！買うことに決めたらまた戻ってくるよ。";
			link.l2.go = "exit";
		break;
		
		case "Wine_ItemTrader_1":
			dialog.text = "どうぞ、ボトルをお取りください。";
			link.l1 = "ありがとう！";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -700);
			TakeNItems(pchar, "potionwine", 1);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			AddQuestRecord("Wine", "1_1");
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles":
			dialog.text = "はっ！俺はただの小売商で、卸売業者じゃねえんだ。そんなにたくさんの瓶を売るには半年以上かかるぜ――あのワインは珍しくて高価なんだ、誰でも買えるもんじゃねえよ。そんなに在庫はないんだ。";
			link.l1 = "わかった、持っていないなら仕方ないさ。\nだが、お前自身はどこかから手に入れてるんだろ？\n仕入れ先の名前を教えてくれれば、そいつから直接買うぜ。\nそれとも、ワインはヨーロッパから届けられてるのか？";
			link.l1.go = "Wine_Bottles_1";
		break;
		
		case "Wine_Bottles_1":
			dialog.text = "いや、違うぜ。ここで手に入れてるんだ。でも、そう簡単に仕入れ先の名前は教えられねえな。だが、千ペソくれりゃ……もしかしたら、教えてやってもいいかもな……";
			if (makeint(Pchar.money) >= 1000)
            {
				link.l1 = "いいだろう。これが千枚だ――さあ、仕入れ先を教えろ。";
				link.l1.go = "Wine_Bottles_2";
			}
			link.l2 = "今やお前ら商売人は図々しくなりすぎだぜ！そんなの、お前らにはもったいないくらいだろ？ お前らの取引先なんかいなくても、俺は十分やっていけるさ、ありがとな。";
			link.l2.go = "Wine_Bottles_fail";
		break;
		
		case "Wine_Bottles_free":
			dialog.text = "そうか……仕方ないな。これがあんたの証文だ、いつか恩を返してくれると期待してるぜ。";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "俺のワインの仕入れ先の名前は "+pchar.questTemp.Wine.Name+"、彼はこの地元の店の主人だ。";
			link.l1 = "了解だ！ありがとな！";
			link.l1.go = "exit";
			//pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Wine_Bottles_2":
    		AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "俺のワインの仕入れ先の名前は "+pchar.questTemp.Wine.Name+"、彼は地元の店の主人だ。";
			link.l1 = "了解だ！ありがとう！";
			link.l1.go = "exit";
			pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "3");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles_fail":
			dialog.text = "承知しました、船長。ご武運を。";
			link.l1 = "またな。";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "4");
			WineTraderQMDel();
		break;
		
		case "Wine_Repeat1":
			DeleteAttribute(pchar, "questTemp.Wine.Repeat1");
			dialog.text = "それはどういう意味だ？説明しろ。";
			link.l1 = "俺を騙しやがったな、この野郎！今さっき店に行ったばかりだぜ、 "+pchar.questTemp.Wine.Name+" 「ワインは絶対に扱わないって、本人が俺にそう言ったんだ！金を返せ！」";
			link.l1.go = "Wine_Repeat1_fail";
			link.l2 = "誤解があったんだ……俺は倉庫番のところへ行って、 "+pchar.questTemp.Wine.Name+" ワインの取引は一度もしたことがないと主張していました。それをどう説明するんだ？";
			link.l2.go = "Wine_Repeat1_1";
		break;
		
		case "Wine_Repeat1_1":
			dialog.text = "へっ！あいつは間違いなくワインを扱ってるぜ。ただし、誰にでもワインを売るわけじゃねえ――他の品も同じだ。理由はいくつかあるんだよ……もしあいつからワインを買いたいなら、俺が紹介状を書いてやるよ。あいつは俺と俺の字を知ってるから、 それを読めばワインを売ってくれるはずだ。もちろん、この親切もタダじゃねえけどな。";
			link.l1 = "なんてことだ！俺から千金も奪いやがったな！";
			link.l1.go = "Wine_Repeat1_2";
		break;
		
		case "Wine_Repeat1_2":
			dialog.text = "情報のためにお前から千ペソ受け取ったぜ。\n手紙については別に二千ペソ払ってもらう。どんな場合でも、それ以下にはならねえぞ。";
			if (makeint(Pchar.money) >= 2000)
			{
				link.l1 = "ああ……商人どもは本当に欲深いな。誰にも好かれねえのも当然だぜ。まあいい、ほらよ、金だ。さっさと証文を書きやがれ。";
				link.l1.go = "Wine_Bottles_3";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "（信用できる）妥協案を出そう。今ここで無料で推薦状をくれれば、後で俺もお前に無料で推薦状を書いてやる。 このワイン取引は始まりにすぎねえんだ。";
				link.l2.go = "Wine_Bottles_free";
			}
			link.l3 = "それはまったく筋違いだぜ！こんな取引、全部やめた方がマシだ。そんなずる賢い守銭奴を儲けさせる気はねえ。 守銭奴ってのはお前のことだ。じゃあな。";
			link.l3.go = "Wine_Repeat1_goaway";
		break;
		case "Wine_Bottles_free":
			dialog.text = "そうか……仕方ないな。これがあんたの証文だ、いつか恩を返してくれるといいがな。";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6_1");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Bottles_3":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "お前は変わった奴だな、船長！まあ、お前の会計係が金の管理をしてるのは分かるが、 たまには自分の頭で考えた方がいいぜ。俺の上乗せなしで、ワインをまとめて卸値で買うチャンスがあるんだ。 かなりの儲けになるぞ。だから、お互いの稼ぎの邪魔はやめようぜ。今はお前の方が欲張りに見えるからな。\nよし…（書きながら）ほら、この手紙を持っていけ― "+pchar.questTemp.Wine.Name+"  何も聞かずにワインを売ってくれる。";
			link.l1 = "そう願いたいね……また何か問題が起きたら、俺は戻ってくるぜ。じゃあな！";
			link.l1.go = "Wine_Bottles_4";
		break;
		
		case "Wine_Bottles_4":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Repeat1_goaway":
			dialog.text = "かしこまりました、船長。ごきげんよう。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "4");
			DelLandQuestMark(npchar);
		break;
		
		case "Wine_Repeat1_fail":
			dialog.text = "「おやおや、脅しに来て無礼な態度を取るつもりかい？それなら衛兵を呼ぶぞ！おい、衛兵！ここだ！」";
			link.l1 = "「ああ、うるせえ！お前の勝ちだ、俺は引き下がる！くたばれ」 "+NPCharSexPhrase(npchar,"","")+"くたばれ、このウミウめ、破滅しちまえ！";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "7");
			DelLandQuestMark(npchar);
		break;
		// <-- мини-квест Дефицитный товар
		
		//Sinistra --> мини-квест "Знакомство с индейцами"
		case "ZsI_PokupaemPistolety":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "ああ、なるほどな。原住民と取引してるのか？この取引でもうずいぶん金を使ったって聞いたぜ、ははっ！";
			}
			else
			{
				dialog.text = "トラブルを予想してるのかい、船長？それともジャングル探検の計画か？ははっ！";
			}
			link.l1 = "それで、取引できるか？";
			link.l1.go = "ZsI_PokupaemPistolety_1";
			DelLandQuestMark(npchar);
		break;
		
		case "ZsI_PokupaemPistolety_1":
			dialog.text = "もちろんです！お客様はいつでも大歓迎ですよ。三千ペソで、ご要望通り信頼できるピストル、弾丸、 火薬をお渡しします。";
			if (sti(pchar.Money) > 2999)
			{
				link.l1 = "高いが、まあいい。買わせてもらうぜ。";
				link.l1.go = "ZsI_PokupaemPistolety_2";
			}
			if (sti(pchar.Money) > 2299)
			{
				link.l2 = "値段が不公平に思えるな。モスクワ人ファディの友人には割引してくれないか？";
				link.l2.go = "ZsI_Torg";
			}
			link.l3 = "三千だと？そりゃあ強盗じゃねえか！さよなら、旦那！";
			link.l3.go = "ZsI_NetDeneg";
		break;
		
		case "ZsI_NetDeneg":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			PChar.quest.ZsI_Timer.over = "yes";
			sld = CharacterFromID("ListKakao");
			sld.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
		break;
		
		case "ZsI_PokupaemPistolety_2":
			dialog.text = "外でも元気でな、船長！";
			link.l1 = "さらばだ、旦那。";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -3000);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_PokupaemPistolety_3":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			PChar.quest.ZsI_Patrul.win_condition.l1 = "location";
			PChar.quest.ZsI_Patrul.win_condition.l1.location = "BasTer_ExitTown";
			PChar.quest.ZsI_Patrul.win_condition = "ZsI_Patrul";
		break;
		
		case "ZsI_Torg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 18)
			{
				Notification_Skill(true, 19, SKILL_COMMERCE);
				dialog.text = "確かに、船長。ファディの友人ならいつでも歓迎だぜ。全部で二千三百でどうだ？";
				link.l1 = "そっちのほうがいいな。もらっておくぜ。";
				link.l1.go = "ZsI_Torg_2";
				AddCharacterExpToSkill(pchar, "Commerce", 30);
			}
			else
			{
				Notification_Skill(false, 19, SKILL_COMMERCE);
				dialog.text = "ファデイ旦那の友人ならいつでも歓迎だが、値段には友人なんていないぜ。三千ペソだ、船長。";
				if (sti(pchar.Money) > 2999)
				{
					link.l1 = "高いけど、まあいいさ。もらっておくぜ。";
					link.l1.go = "ZsI_PokupaemPistolety_2";
				}
				link.l2 = "三千だと？そりゃ強盗じゃねえか！さよなら、旦那！";
				link.l2.go = "ZsI_NetDeneg";
				//Log_info("Trading skill is not sufficient");
				AddCharacterExpToSkill(pchar, "Commerce", -30);
			}
		break;
		
		case "ZsI_Torg_2":
			dialog.text = "外でも元気でな、船長！";
			link.l1 = "さらばだ、旦那。";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -2300);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		// <-- мини-квест "Знакомство с индейцами"
		
		// --> Цена чахотки
		case "Consumption":
			dialog.text = "いや、違う……今は邪魔しないでくれ、私はとても忙しいんだ……なんて馬鹿げた質問だ……";
			link.l1 = "そうか。時間を無駄にして悪かったな……";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		// <-- Цена чахотки
		//Jason --> генератор Неудачливый вор
		case "Device_ItemTrader":
			dialog.text = "「ふむ、」 "+pchar.GenQuest.Device.Shipyarder.Type+"？今まで聞いたことがねえな……それはいったい何なんだ？俺の人生でそんなもの聞いたこともねえぞ"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "「まあ、船大工の道具だぜ。」 "+pchar.GenQuest.Device.Shipyarder.Describe+"。そんなものを誰かがあなたに勧めたのか？";
			link.l1.go = "Device_ItemTrader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_ItemTrader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 0 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 4 && npchar.location.group == "merchant" && npchar.location.locator == "merchant"+sti(pchar.GenQuest.Device.Shipyarder.Chance1))
			{
				dialog.text = "ふむ……ああ、変な奴が一人いたな。でもあいつはそれが何なのか教えてくれなかったし、ただ俺に売りつけようとしただけだ。 だけど、何に使うものか分からないのに、俺がそれを買ってどうする？どうやって転売するんだ？だから、 俺は断ったのさ"+NPCharSexPhrase(npchar,"","")+"、そして彼は立ち去った";
				link.l1 = "それで、そいつはどんな奴だったんだ？どこへ行った？俺はその道具がどうしても必要なんだ。";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "いや、そんなことはない。悪いが、力になれねえ。周りの連中に聞いてみな。";
				link.l1 = "なるほど。さて、聞き込みを始める時だな！";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		// Мангароса
		case "mangarosa":
			// тут работает везение
			if (sti(pchar.questTemp.Mangarosa.m_count) == 5 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+hrand(30)+hrand(40, "1"))
			{
				dialog.text = "見せてくれ……そうだな、これは面白い植物だ。そして、とても、とても珍しいものだ。マンガローザと呼ばれている。 何に使うのかは知らないが、これについて面白い事実があるんだ……";
				link.l1 = "「どういう意味だ？」";
				link.l1.go = "mangarosa_1";
			}
			else
			{
				dialog.text = LinkRandPhrase("見せてくれ……ふむ、これは面白い植物だな。だが残念ながら、それ以上のことは俺にはわからん。もし何かに使われているとしても、 俺には分からないんだ。","そうだな……ふむ……薬草みたいだが、俺にはさっぱり分からねえ。悪いが、力になれねえよ。","どこだ？うーん……いや、これは見たことがねえな。確かに面白そうだが、何に使うものか全然わからねえ……");
				link.l1 = "なるほど。まあ、もう少し聞き込みしてみるよ。悪いな。";
				link.l1.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_exit":
			DialogExit();
			pchar.questTemp.Mangarosa.m_count = sti(pchar.questTemp.Mangarosa.m_count)+1;
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_1":
			dialog.text = "放浪のジプシーや野蛮人たちは、これらの植物に大変興味を示すんだ。\n俺は一度、ジプシーがこんな茎一本に一握りの金貨を払うのを見たことがある。\nだが、なぜ彼らがそれを必要とするのかは全く分からねえ。";
			link.l1 = "なるほど……まあ、少なくとも何かは分かったぜ！これで次にどこで聞けばいいか分かった。どうもありがとう！";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.m_count");
			pchar.questTemp.Mangarosa = "gipsy";
			AddQuestRecord("Mangarosa", "2");
		break;
		
		//--> Украденное воспоминание
		case "UV_Lavochniki_1":
			dialog.text = "「残念ながら、」 "+GetAddress_Form(NPChar)+"、うちの店にはこんな上等な品物は何ヶ月も入ってきていません。 この厳しい時代には贅沢品への欲もすっかり衰えてしまいました。 私の店に来る庶民たちはせいぜい質素な小物しか買えませんし、上流階級の方々 はめったに私のつましい品を見てくださることもありません。";
			link.l1 = "「よし…」";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki");
			pchar.questTemp.UV_Lavochniki_2 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_2":
			dialog.text = "誠に遺憾ながら、船長、これほど見事な品々はしばらく当店に並んでおりません。 この港の裕福な客人たちは滅多に私のささやかな店に足を運ばず、 常連のお客様も手持ちの乏しい財布で買える物しか求めません。";
			link.l1 = "よろしい……";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_2");
			pchar.questTemp.UV_Lavochniki_3 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_3":
			dialog.text = "ああ、船長、なんと間の悪いことか……ほんの数時間前に、実に見事なネックレスを手放したばかりなのです――裕福な別の船長が購入していきました。私の店では、 目の肥えたご婦人の心さえも溶かすような品を常に取り揃えております\nもしよろしければ、明日またお越しになってはいかがでしょう？ジゼル……つまり……私の仕入れ先が、きっとあなたの憧れの方を永遠に虜にするような宝物を用意できるはずです。";
			link.l1 = "私には時間という贅沢はありませんので、その品をすぐに必要としています。さて、 その首飾りを手に入れた幸運な船長の名前を教えていただけますか？";
			link.l1.go = "UV_Lavochniki_3_1";
		break;

		case "UV_Lavochniki_3_1":
			dialog.text = "「トリスタン・ルニエ、『ゴールデン・シーガル』の船長だ。彼の船は今も我々の港に停泊している。\nただ、正直に言えば、あの宝を彼が手放すかどうかは疑わしい。もし彼が応じなければ、明日また私のところへ来てくれ。 \n名誉にかけて、船長、必ずや満足のいく取り決めを用意しよう。」";
			link.l1 = "...";
			link.l1.go = "UV_Lavochniki_exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_3");
			AddDialogExitQuestFunction("UV_GoldSeagull");
		break;
		
		case "UV_Lavochniki_exit":
			DialogExit();
			AddQuestRecord("UV", "3");
			/*AddQuestUserData("UV", "sSex", NPCharSexPhrase(NPChar,"ца","ки"));
			AddQuestUserData("UV", "sSex1", NPCharSexPhrase(NPChar,"ец","ка"));
			AddQuestUserData("UV", "sSex2", NPCharSexPhrase(NPChar,"","а"));*/
		break;
		//<-- Украденное воспоминание
		
// ======================== блок нод angry ===============>>>>>>>>>>>>>>>

////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok")
		break;

// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
