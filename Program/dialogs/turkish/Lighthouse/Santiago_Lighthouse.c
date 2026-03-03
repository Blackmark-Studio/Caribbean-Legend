// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsun?","Ne bilmek istersiniz?"),"Ne istiyorsun, "+GetAddress_Form(NPChar)+"?","Bu üçüncü kez bana bunu sormaya çalışıyorsun...","Senden bıktım, defol git!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Üzgünüm, fikrimi değiştirdim.","Önemli değil, kusura bakmayın."),"Unuttum, kusura bakmayın...","Üçüncü seferde olacak galiba, ha? Affedersin...","Affedersin, affedersin! O zaman ben çıkayım...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak")
			{
				link.l1 = "Selamlar. Santiago'nun engizitörü Padre Vincento, mektubunda sizden bahsetti. Bana yardımcı olabileceğinizi söyledi.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak_next")
			{
				link.l1 = "Padre Vincento'dan bir haber var mı? "+npchar.name+"?";
                link.l1.go = "guardoftruth_5";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && CheckCharacterItem(pchar, "jewelry33") && CheckCharacterItem(pchar, "jewelry34") && CheckCharacterItem(pchar, "jewelry35"))
			{
				link.l1 = "Padre Vincento'yu görmem lazım. İlgilendiği eşyaları buldum.";
                link.l1.go = "guardoftruth_7";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "inquisition")
			{
				link.l1 = "Yani, "+npchar.name+", Padre Vincento sana ne söyledi?";
                link.l1.go = "guardoftruth_11";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Elbette, Señor. Padre Vincento'nun bizzat sizinle iş yaptığına göre, siz oldukça saygın bir adamsınız.";
			link.l1 = "Harika. O zaman sen bizim haberci oluyorsun. Şimdi dinle, bu adam Padre Vincento için çok önemli. Artık onun sorumluluğu sende, onu Santiago'ya götürmeli ya da bunu yapacak birini bulmalısın.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "...";
			link.l1 = "Engizitör adına mahkûmdan sen sorumlusun. Zincirlerini çözmeni tavsiye etmem, Gaius Marchais güçlü bir adamdır. Bu mektubu Padre Vincento'ya ver ve ona iki gün içinde cevabını beklediğimi söyle. Umarım bu yeterli olur.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			Log_Info("You part with the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Anlaşıldı, Señor. Elimden gelenin en iyisini yapacağım. Kutsal babaya ilk kez yardım etmiyorum.";
			link.l1 = "Hepsi bu değil. Carraca San Gregorio'nun kaptanı Carlos Guevara burada olmalıydı. Bana vanilya getirecekti. Mektubumu sana verdi mi?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Evet, yükünüz sağlam ve sizi bekliyor, Señor.";
			link.l1 = "Pekâlâ, o zaman onu gemime çektireceğim. Padre Vincento'nun cevabını beklerken iki gün burada olacağım. Şimdilik bu bir veda değil, "+npchar.name+"!";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			LocatorReloadEnterDisable("mayak9", "boat", false);
			ref sld = characterFromId("GOT_Marshe");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakNextStage", 0, 0, 2, false);
			SetCharacterGoods(pchar, GOOD_CINNAMON, GetCargoGoods(pchar, GOOD_CINNAMON) + sti(pchar.questTemp.Guardoftruth.VanilleQty));
			AddQuestRecord("Guardoftruth", "21");
		break;
		
		case "guardoftruth_5":
			dialog.text = "Evet, Señor. İşte Padre Vincento'dan bir mektup. Senden çok memnun, gerisini mektuptan öğrenirsin.";
			link.l1 = "Harika. O zamana kadar, "+npchar.name+". Ve şimdilik - hoşça kal.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_exit";
			GiveItem2Character(pchar, "specialletter");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_next";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Pekâlâ. Onları bana ver, ben de onları Kutsal Baba'ya götüreyim.";
			link.l1 = "Olmaz dostum! Onları elde etmek kolay olmadı ve öylece teslim etmem. Sadece Padre Vincento'ya bizzat veririm.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Ama señor! Beni dolandırmadığınızı nasıl bilebilirim?";
			link.l1 = "Bakın: bu buhurdan, bu kâse ve lâpislazuli taşlı haç... "+npchar.name+", beni kim sanıyorsun? Gerçekten onları almadan Engizisyon'a gidecek kadar aptal olduğumu mu düşünüyorsun?";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Beni affedin, señor... Yarın gelin, gelişinizi Padre Vincento'ya anlatacağım.";
			link.l1 = "İyi. Yarın görüşürüz.";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakLastStage", 0, 0, 1, false);
		break;
		
		case "guardoftruth_11":
			dialog.text = "Majesteleri sizi kabul edecek, Señor. Ziyaretinizi geciktirmeyin. İşte belge, bunu askerlere gösterin, sizi içeri alacaklardır. Ama önce bir İspanyol bayrağı çekin, yoksa askerler sizi tutuklayabilir.";
			link.l1 = "Anladım. O zaman İspanyolca. Teşekkürler dostum! Hemen yola çıkıyorum!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper");
			pchar.questTemp.Guardoftruth = "santiago";
			AddQuestRecord("Guardoftruth", "34");
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 400);//скрытность
			GuardOT_SetPadreVincento();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
