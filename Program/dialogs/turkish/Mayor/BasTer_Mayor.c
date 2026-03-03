// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsunuz? Sorunuzu sorun.","Sizi dinliyorum, sorun nedir?"),"Bu soruyu ikinci kez sormaya çalışıyorsunuz...","Bu, tekrar sormaya üçüncü teşebbüsünüz...","Bu ne zaman bitecek?! Ben meşgul bir adamım, koloninin işleriyle uğraşıyorum, sen ise hâlâ bir şeyler sormaya çalışıyorsun!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şimdi değil. Yanlış yer ve zaman."),"Doğru... Ama sonra, şimdi değil...","Soracağım... Ama birazdan...","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Sizin için hassas bir meselem var. Kısa bir süre önce bir korsan, lazurit taşlı altın bir haçı Basse-Terre cemaatine bağışladı. Ancak sorun şu ki, bu haç Santiago cemaatinden çalındı ve hırsızlık sırasında bir din adamı öldürüldü...";
                link.l1.go = "guardoftruth";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Vali General Philippe de Poincy'nin emriyle silahlı fırkateyninizin komutasını devralmak üzere geldim.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l1 = "Firkateyni filoya katmaya hazırım.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
			{
				link.l1 = "Burada biriyle bir görüşmem var...";
                link.l1.go = "baster_goldengirl";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_guber_1"))
			{
				link.l1 = "Monsieur, kasaba içinde ticari faaliyetlerde bulunmayı düşünüyorum. Özellikle, düzenli ve büyük ölçekli içki ticaretiyle ilgileniyorum.";
				link.l1.go = "TPZ_guber_1";
			}
			//<-- Торговля по закону

		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Zaten her şeyi aldınız. Daha ne istiyorsunuz?","Henüz el koymadığın bir şey kaldı mı?");
            link.l1 = RandPhraseSimple("Sadece etrafa bakıyorum...","Sadece kontrol ediyorum, bir şeyi almayı unutabilirim...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "Hm. Oldukça ilginç. Ama neden İspanyolların sorunlarıyla ilgileneceğimi düşünüyorsun?";
			link.l1 = "Bu İspanyollarla ilgili değil, Mösyö. Din insanları milliyetlerine göre ayırmaz. Cemaatinizde kutsal hizmetkârın kanına bulanmış bir eşya var ve Santiago'nun cemaatinde bir kutsal saygısızlık işlendi...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "Sizden adalet göstermenizi ve kutsal babaya haçı asıl sahiplerine geri vermesini emretmenizi rica ediyorum.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Ve ne zamandan beri böyle gerçek ve samimi bir inanan oldun, ha, "+pchar.name+"  İspanyollar bizim dostumuz değil ve bu konuda kutsal babaya baskı yapmam için bir sebep göremiyorum. Haç bir hediyeydi ve bu yeterli. Papazımızın o hırsızlık ve cinayetle hiçbir ilgisi yok, yani...";
			link.l1 = "Ve bana yardım edemezsin, değil mi?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Açıkçası, "+pchar.name+", Bunu yapmak zorunda olduğumu düşünmüyorum. O Papist fanatiklerine karşı hiçbir sevgi beslemiyorum.";
			link.l1 = "Anladım. Sizi rahatsız ettiğim için üzgünüm, Mösyö...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Gemi hazır, fakat filonuzda onun için boş bir yer yok. Kaptan, filonuzu küçültüp geri dönün, o zaman hemen size fırkateyni vereceğim.";
				link.l1 = "Pekâlâ.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Evet, elbette, gemi sefere hazır. Kaptanı durumu biliyor ve tüm emirlerinizi yerine getirecek.";
				link.l1 = "O halde yola çıkıyoruz. Hoşça kalın, Ekselansları.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Mükemmel. Yeni geminizi karşılamaya hazırlanın. Kaptanı bilgilendirildi ve tüm emirlerinizi yerine getirecek.";
			link.l1 = "O halde yola çıkıyoruz. Hoşça kalın, Ekselansları.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "baster_goldengirl":
			dialog.text = "Ah, Monsieur Charles de Maure, tam zamanında geldiniz! Eski dostum sizinle tanışmak için sabırsızlanıyor ve bana gelişinizi haber vermemi rica etti. Lütfen, oturma odama buyurun, Angerran'a hemen haber vereceğim. Bu arada, siz ikiniz nasıl tanıştınız?";
			link.l1 = "Birlikte kumar oynadık. Kaybetti, biraz tartıştık. Sanırım Monsieur de Chievous aramızdaki meseleyi düzeltmek istiyor.";
			link.l1.go = "baster_goldengirl_1";
		break;
		
		case "baster_goldengirl_1":
			dialog.text = "Şüphesiz! Umarım aranızdaki meseleleri halledersiniz. Angerran belki en hoş insan değildir, ama akıllı ve onurludur, tıpkı sizin gibi. Bu, nadir bulunan bir nitelik.";
			link.l1 = "Beni onurlandırıyorsunuz, Ekselansları. Eğer izin verirseniz, onu bekleme salonunda bekleyeceğim.";
			link.l1.go = "baster_goldengirl_2";
		break;
		
		case "baster_goldengirl_2":
			dialog.text = "Elbette, keyfinize bakın, kendinizi evinizde hissedin. Biraz beklemeniz gerekebilir. Birkaç içki getirmelerini söyleyeceğim.";
			link.l1 = "Teşekkür ederim, Ekselansları, ama ben almayayım. Sadece oturup ortak... dostumuzu bekleyeceğim.";
			link.l1.go = "baster_goldengirl_3";
		break;
		
		case "baster_goldengirl_3":
			DialogExit();
			pchar.questTemp.GoldenGirl = "baster1";
			DoQuestReloadToLocation("CommonResidence_3", "reload", "reload1", "GoldenGirl_AngerranInResidence");
		break;
		
		//--> Торговля по закону
		case "TPZ_guber_1":
			dialog.text = "Kaptan, bana yaklaşmakla akıllıca davrandınız. Bu adada yasa dışı ticaretle mücadele etmek için her türlü çabayı gösteriyoruz ve işlerini yasal yollarla yürütmek isteyen dürüst kaptanları gerçekten memnuniyetle karşılıyorum.";
			link.l1 = "Öyleyse, ticarete başlamak için gereken şartlar ve adımlar nelerdir?";
			link.l1.go = "TPZ_guber_2";
			DelLandQuestMark(npchar);
		break;

		case "TPZ_guber_2":
			dialog.text = "Oldukça basit. İçki ticareti yapmak için, hazineye aylık yüz doblon vergi ödemeniz, düzgün kayıtlar tutmanız ve düzenli faaliyet raporları sunmanız gerekir. Parayı yatırdıktan sonra, ticarete gönül rahatlığıyla başlayabilirsiniz.";
			link.l1 = "Mükemmel. Şartlar tamamen makul. Christian Deluce adında bir yerli, benim adıma hareket edecek. Bunun bir sorun oluşturmayacağını umuyorum?";
			link.l1.go = "TPZ_guber_3";
		break;

		case "TPZ_guber_3":
			dialog.text = "Dediğiniz gibi olsun, Kaptan. Ancak unutmayın – himayenize aldığınız kişinin tüm sorumluluğu sizin omuzlarınızda olacak. Eğer o bir hata yaparsa, sonuçlarına siz de katlanacaksınız.";
			link.l1 = "Elbette. Açıklamanız için teşekkür ederim, Vali. Gerekli düzenlemeleri yapacağız ve Christian vergi ödemesiyle ilgilenecek.";
			link.l1.go = "TPZ_guber_4";
		break;

		case "TPZ_guber_4":
			dialog.text = "Harika.   Böyle özverili bir yaklaşım görmek beni memnun etti.   Girişiminizde başarılar dilerim.";
			link.l1 = "Çok teşekkür ederim. İş birliğimizin şehre fayda sağlayacağına inanıyorum. Hoşça kalın.";
			link.l1.go = "TPZ_guber_5";
		break;

		case "TPZ_guber_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TPZ_guber_1");
			AddQuestRecord("TPZ", "11");

			sld = CharacterFromID("TPZ_Kristian");
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_21";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
