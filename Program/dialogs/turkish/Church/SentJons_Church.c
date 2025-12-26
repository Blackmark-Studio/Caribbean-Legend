// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular, "+GetSexPhrase("evladım","kızım")+"?","Sor, dinliyorum..."),"Dinliyorum, şimdi konuş. "+GetSexPhrase("evladım","kızım")+"...","Üçüncü kez, "+GetSexPhrase("evladım","kızım")+", neye ihtiyacın varsa sor.","Bir din adamının çok işi var ve sen beni oyalıyorsun, "+GetSexPhrase("evladım","kızım")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda değil, padre..."),"Söyleyecek bir şeyim yok, özür dilerim.","Soracağım, ama sonra. Beni affedin, baba.","Affedersiniz, kutsal baba...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_pastor"))
			{
				link.l1 = "Kutsal Baba, Thomas Morrison'ın kızı hakkında konuşmak istiyorum.";
                link.l1.go = "dwh_pastor_1";
			}
			if (CheckAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi"))
			{
				link.l1 = "Kutsal Baba, Thomas bana tövbe yolunu kabul ettiğini, kendini iyi işlere adayacağını ve ne pahasına olursa olsun cemaate yeni bir çan sağlayacağını iletmemi istedi.";
                link.l1.go = "dwh_pastor_VD_5";
			}
			// <-- Тёмные воды исцеления
		break;

		// --> Тёмные воды исцеления
		case "dwh_pastor_1":
			dialog.text = "Konuş, evladım, seni dinliyorum.";
			link.l1 = "Biliyorum, çingenenin kıza yardım etmesine karşısın. Ama bir babayı, kızını kurtarmak için en ufak bir umudu bile reddetmeye nasıl zorlayabilirsin? Yöntemleri tartışmalı olabilir, ama belki de yardım edebilecek bir bilgisi var.";
			link.l1.go = "dwh_pastor_2";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_2":
			dialog.text = "Oğlum, yalnızca Rab kızı iyileştirebilir. Onun planına olan inanç, bizi zorluklardan geçirir. Eğer Thomas içtenlikle dua eder, Tanrı'nın sözünü takip eder ve kiliseye cömertçe bağışta bulunursa, Rab onun dualarını işitir ve merhamet gösterir.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Güvenilir) Ama sen bile kabul etmelisin ki, Rab insanları aracılığıyla hareket eder. Ya çingene sadece O'nun iradesinin bir aracıysa? Ya O'nun planı öylesine derinse ki, biz sıradan ölümlüler bunu kavrayamıyorsak? Rab gizemli yollarla çalışır, öyle değil mi?";
				link.l1.go = "dwh_pastor_VD_1";
				Notification_Perk(true, "Trustworthy");
			}
			else
			{
				link.l1 = "Bir babaya, kızının gözlerinin önünde eriyip gitmesini izlettiriyorsun, ona yardım etme şansı vermek yerine. Buna merhamet mi diyorsun?";
				link.l1.go = "dwh_pastor_bez_VD_1";
				Notification_Perk(false, "Trustworthy");
			}
		break;

		case "dwh_pastor_VD_1":
			dialog.text = "Sözleriniz bilgece, Kaptan. Ama yine de, sapkınlığın cemaatimizin kalbine sızmasına ve en sadık evlatlarından birinin inancını sarsmasına izin veremem.";
			link.l1 = "Kızını kaybetmekten daha fazla hiçbir şey onun inancını sarsamazdı. Ama ona günah sayılan yolları bile kullanmasına izin verirseniz, inancı zayıflamak yerine daha da güçlenecektir.";
			link.l1.go = "dwh_pastor_VD_2";
		break;

		case "dwh_pastor_VD_2":
			dialog.text = "Ama... bu, cemaatin geri kalanı için nasıl bir örnek olurdu?";
			link.l1 = "Kilise körü körüne cezalandırmaz, doğru tövbeye yönlendirir ve rehberlik eder; bunun bir örneğidir. Kutsal Kitap, içten bir tövbenin ve iyi işlerin günahı affettirebileceğini öğretmiyor mu? Kiliseye cömert bir bağış, kurtuluşa giden yolda ilk adım olabilir.";
			link.l1.go = "dwh_pastor_VD_3";
		break;

		case "dwh_pastor_VD_3":
			dialog.text = "Belki de haklısınız, Kaptan. Thomas'a bu şansı vermeye hazırım. Ama şunu bilin ki—eğer doğru yoldan sapar ve inancını kaybederse, bunun sorumluluğunu siz de taşıyacaksınız! Bağışlara gelince—kilisenin zenginliğe ihtiyacı yok, ihtiyacımız olan her şeye sahibiz. Yalnızca... çan, İspanyol baskını sırasında zarar gördü...";
			link.l1 = "Sözlerinizi Thomas'a ileteceğim. Vaktiniz için teşekkür ederim, Kutsal Baba. Tanrı sizi korusun.";
			link.l1.go = "dwh_pastor_VD_4";
		break;

		case "dwh_pastor_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_11";
		break;

		case "dwh_pastor_bez_VD_1":
			dialog.text = "Bu kalpsizlik değil, Kaptan, bu inançtır. Kızın kaderini terk etmiyoruz, onu Rab'bin ellerine bırakıyoruz. Thomas dua eder, inanır ve alçakgönüllülükle beklerse, eminim ki Rab dualarımızı işitecek ve onu iyileştirecektir.";
			link.l1 = "Biliyor musun, adanın soyluları, vali de dahil, çingenenin hizmetlerinden faydalandı. Ve onlar aforoz edilmedi. O zaman neden Thomas'a bu kadar katısın?";
			link.l1.go = "dwh_pastor_bez_VD_2";
		break;

		case "dwh_pastor_bez_VD_2":
			dialog.text = "Elbette biliyorum, evladım. Ama onlar henüz Rabbin gerçek ışığına erişememiş kayıp ruhlar. Thomas ise cemaatimizin temel direklerinden, en iyilerinden biri. Kötülüğün onun inancını sarsmasına izin vermek tüm kiliseyi tehlikeye atar, böyle ağır bir günaha göz yumamam.";
			link.l1 = "Yani en ufak bir şans bile vermeyi reddediyorsun? Bu gerçekten adil mi?";
			link.l1.go = "dwh_pastor_bez_VD_3";
		break;

		case "dwh_pastor_bez_VD_3":
			dialog.text = "Kurtuluş dediğiniz şey felakete yol açabilir. Bunu tecrübeyle söylüyorum. Bir keresinde, istemeyerek de olsa, onun gibi bir şifacı yeğenimi tedavi etti. Küçük bir kızdı, acı içinde öldü. Ve ruhunun o ayinlerle mahvolup mahvolmadığını yalnızca Tanrı bilir. Beni ikna etmeye çalışmayın—boşuna.";
			link.l1 = "Pekâlâ. Son kararınız buysa, daha fazla ısrar etmeyeceğim. Tanrı sizi korusun.";
			link.l1.go = "dwh_pastor_bez_VD_4";
		break;

		case "dwh_pastor_bez_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			
			AddQuestRecord("DWH", "4");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetCitizenType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_6";
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			LAi_CharacterEnableDialog(sld);
		break;

		case "dwh_pastor_VD_5":
			dialog.text = "Mükemmel, evladım. Yeni bir çan, onun Rab'be ve kiliseye olan bağlılığının bir simgesi olacak. Gerekeni yapmasına izin ver, ama ona hatırlat—Yüce Allah'ın gözü her işi görür ve hiçbir şey O'nun iradesinden kaçamaz.";
			link.l1 = "Öyle olsun, Kutsal Baba. Elveda.";
			link.l1.go = "dwh_pastor_VD_6";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_VD_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_15";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "barmen", "bar1");
			DelLandQuestMark(sld);
			LAi_RemoveLoginTime(sld);
		break;
		// <-- Тёмные воды исцеления
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
