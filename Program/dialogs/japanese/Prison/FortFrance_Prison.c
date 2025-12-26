// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "話せ、聞いてやる";
			link.l1 = "俺が間違ってた。じゃあな。";
			link.l1.go = "Exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "役人、あんたの牢にフォルケ・デルークって男がいると聞いたんだ。あいつを釈放させるために俺にできることはあるか？ ";
                link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "おい、役人、またフォルケ・デリュク囚人の件で来たぜ。こいつの借金の権利は俺が買い取った。だから、 この男を釈放して俺に引き渡してもらいたい。これが借用書だ、確認しろ。\n";
                link.l1.go = "Sharlie_3";
			}	
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Deluck"))
			{
				link.l1 = "ごきげんよう、役人殿。俺の部下について聞きたいんだが…";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_DeluckSvoboda"))
			{
				link.l1 = "書類はここにある、さあ俺の仲間を解放しろ。";
                link.l1.go = "Del_DeluckSvoboda";
			}
			//<-- Миниквест "Делюк"
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "ああ、その水夫か？うちの銀行家からかなりの金を借りて返さず、逃げようとまでしたんだ。だがすぐに見つかった。 それ以来、あいつは拘留されていて、借金を返すまでここにいることになる。";
			link.l1 = "ふん。牢屋にいるままで、どうやってそんなことをするつもりだ？";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "そんなことはどうでもいい、旦那。";
			link.l1 = "おかしいな……で、この哀れな奴は一体いくら借りてるんだ？";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "知らねえな。銀行家に聞けば詳しく教えてくれるぜ。";
			link.l1 = "なるほど。情報をありがとう、役人。";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskiper";
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", false);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Sharlie_3":
			Log_Info("You have given debt papers");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
			dialog.text = "ふむ。すべて正しいな。本当にその囚人を釈放してほしいのか？";
			link.l1 = "ああ。あいつには借金を返してもらう必要があるんだ、そしてその方法も俺は知ってるぜ。";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "よし、断る理由はねえ。すぐにデリュクをここへ連れてこさせる。ただし警告しておくが、 あの狐野郎は隙あらば逃げ出すぜ、あいつに幻想なんか抱くんじゃねえぞ。";
			link.l1 = "わかった、役人。今から俺の借金者を引き取りたい。";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "ああ、もちろんだ。軍曹！囚人を連れてこい！フォルケ・デルック、どうやら今は新しいご主人様ができたようだな！";
			link.l1 = "...";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			DialogExit();
			// создаем штурмана
			sld = InitFolke("Folke", "Deluc");
			pchar.questTemp.Sharlie = "takeskiper";	
			ForceHeroAutolevel(sld);
			AddDialogExitQuestFunction("Del_Turma");
		break;
		//<-- Бремя гасконца
		
		//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
		case "Del_Deluck":
			DelLandQuestMark(npchar);
			dialog.text = "はっ！おいおい、お前さんの窮地の噂はサン・ピエールの連中をしばらく楽しませるだろうぜ。\nだが気にするな、船長。お前さんは明らかに運が悪かっただけだ。\nさあ中へ入りな、心配はいらねえ――お前の航海士もこの話から逃げられねえからな、ははっ！";
			link.l1 = "おかしいな。ありがとう、役人。";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_prison");
		break;
		
		case "Del_DeluckSvoboda":
			dialog.text = "了解だ、船長。指示通りに進めるぜ。";
			link.l1 = "...";
			link.l1.go = "Del_DeluckSvoboda_2";
			Log_Info("You have given debt papers");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
		break;
		
		case "Del_DeluckSvoboda_2":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_10";
			
			AddDialogExitQuestFunction("Del_Turma");
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
