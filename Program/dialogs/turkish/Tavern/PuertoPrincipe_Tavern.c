// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Bana kısa bir süre önce bir soru sormaya çalıştın, "+GetAddress_Form(NPChar)+"...","Bugün boyunca bu soruyu üçüncü kez gündeme getiriyorsun...","Sanırım daha fazla sorunuz var?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Evet, gerçekten de üçüncü kez...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_1"))
			{
				link.l1 = "Söylentilere göre birileri değerli cinini elinden almış. Yoksa dedikodular asılsız mı?";
				link.l1.go = "OS_Tavern1_1";
			}
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_3"))
			{
				link.l1 = "İyi haberler, "+npchar.name+"! Fıçını geri getirdim!";
				link.l1.go = "OS_Tavern3_1";
			}
		//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern1_1":
			dialog.text = "Tanrı aşkına, doğruymuş. Başka ne duydun? Bir şey biliyor musun? Ne olur, bana nerede bulacağımı bildiğini söyle. Eğer onu geri alamazsam... bu şehirden kaçmam gerekecek. Ya kendi ayaklarım üzerinde ya da bir tabutun içinde.";
			link.l1 = "Gerçekten de, durumun pek parlak görünmüyor dostum. Hayır, sadece talihsizliğinle ilgili bazı söylentiler duydum. Böylesine değerli bir yük nasıl oldu da elinden kayıp gitti?";
			link.l1.go = "OS_Tavern1_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern1_2":
			dialog.text = "Lanet olsun... Ne diyebilirim ki? Gözümün önünden çalındı! Fıçı sabah burada kesinlikle vardı. İki gün önce gelmişti, güvenlik için gece eve götürdüm. Sabah olunca geri getirdim, tezgahın altına sakladım. Akşam olduğunda ise hiçbir iz bırakmadan kaybolmuştu! Kimse bir şey görmedi ya da duymadı.";
			link.l1 = "Vay canına...";
			link.l1.go = "OS_Tavern1_3";
		break;

		case "OS_Tavern1_3":
			dialog.text = "En ufak bir fikrim olsaydı, çoktan peşine düşmüştüm. Ama ne yazık ki hiçbir iz yok – sanki o fıçı bu dünyaya fazla kıymetliydi de gökler onu kendine aldı. Kim geri getirirse ona yüz elli dublon ödeyeceğim. Dahası, adını tavernama asacağım bir levhaya yazacağım ki herkes kahramanlığını bilsin!";
			link.l1 = "Ne yapabileceğime bakarım. Bu levha işini sonra tekrar konuşuruz. Onun yerine bana söyle, bu fıçıdan kimlerin haberi vardı? Ve senden başka tezgahın arkasında kim olmuş olabilir?";
			link.l1.go = "OS_Tavern1_4";
			link.l2 = "Bir fıçı için yüz elli dublon mu? Komik. Ama senin derdin beni ilgilendirmez. Kendi başının çaresine bak.";
			link.l2.go = "OS_Tavern1_end";
		break;

		case "OS_Tavern1_end":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			CloseQuestHeader("OS");

			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			sld = CharacterFromID("OS_Pirate");
			sld.lifeday = 0;
		break;

		case "OS_Tavern1_4":
			dialog.text = "Hiç kimse yoktu! Belki hizmetçi kızım dışında, ama bu imkânsız. O gün meyhanede tam bir curcuna vardı – 'Deniz Canavarı'nın tayfası avdan güzel bir ganimetle dönmüştü. Kızcağızın bir an bile dinlenmeye vakti olmadı, bırak arka tarafa gizlice geçmeyi, tezgâhın arkasına bile uğrayamadı.";
			link.l1 = "Bundan emin misin?";
			link.l1.go = "OS_Tavern1_5";
		break;

		case "OS_Tavern1_5":
			dialog.text = "Hiç şüphe yok! Durmaksızın çalışmak ona göre değildi, akşam olunca da yay gibi gerilmişti. Denizcilerden biri ona asılınca öyle bir yaygara kopardı ki, neredeyse bütün mekanı sağır etti. Düzeni sağlamak için yerimden kalkmak zorunda kaldım. Ama tuhaf, normalde böyle yaklaşımları çok daha soğukkanlı karşılar.";
			link.l1 = "Hepsi bu mu? O gün başka olağanüstü bir şey olmadı mı?";
			link.l1.go = "OS_Tavern1_6";
		break;

		case "OS_Tavern1_6":
			dialog.text = "While I was quelling that first disturbance, another flared up - two sailors came to blows in the far corner. The scuffle didn't last long, though; they appeared to be shipmates, and were quickly separated. After that, everything truly quieted down with nothing further worthy of mention.";
			link.l1 = "Pekâlâ, aramaya başlayacağım. Bekle. Sanırım fıçı yakında tekrar senin, hımm... dikkatli gözlerinin önünde olacak.";
			link.l1.go = "OS_Tavern1_7";
		break;
		//<-- Старые счёты
		
		case "OS_Tavern1_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			AddQuestRecord("OS", "2");
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Matros_1", "citiz_31", "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "OS_Matros";
			LAi_SetImmortal(sld, true);
			sld.City = "PuertoPrincipe";
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto14");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "OS_Tavern3_1":
			dialog.text = "Buldunuz mu?! Gerçekten olabilir mi? Kaptan, hayatımı kurtardınız! Bunun arkasında kim vardı? O alçağın adını bilmeliyim!";
			link.l1 = "Bu, 'Deniz Canavarı'nın kaptanıyla iş birliği yapan Jack Veils adlı birinin titizlikle planladığı bir oyundu. Kendi tayfalarını topladılar ve seni uzaklaştırmak için karmaşık bir dikkat dağıtma düzeni kurdular. Sen yerinden ayrıldığında, varil korumasız kaldı ve onlar da kolayca onu alıp götürdüler.";
			link.l1.go = "OS_Tavern3_2";
			DelLandQuestMark(npchar);
			pchar.questTemp.CameraDialogMode = true;
		break;

		case "OS_Tavern3_2":
			dialog.text = "Aman Tanrım! Jack Veils! Demek geri döndü... Ve anlaşılan meyhaneyi böyle sinsi yollarla geri almayı düşündü. O tilki asla yenilgiyi kabul etmez!";
			link.l1 = "Yani, bir zamanlar bu mekânın sahibiymiş? İçiniz rahat olsun, artık bir daha iş çeviremeyecek. Onu öteki tarafa yolladım.";
			link.l1.go = "OS_Tavern3_3";
		break;

		case "OS_Tavern3_3":
			dialog.text = "Kaptan! Bu olağanüstü bir şey! Beni... beni günlerimi gölgeleyen o sürekli korkudan kurtardınız! Onun er ya da geç döneceğini hep biliyordum... Birkaç yıl önce, bu meyhanenin sahipliği için rakiptik ve o beni alt etmeyi başardı\nAma zaferin sevinci onun sonunu getirdi – kutlama coşkusuyla, farkında olmadan meyhaneyi bana kart oyununda kaybetti. Tabii ki, sabah olunca soluğu burada aldı, yalvarıp yakardı, meyhaneyi geri almak için her şeyi vadetti\nAma öyle kolayca kandırılacak biri değilim. Sonra ortadan kayboldu... Bu işin peşini bırakmayacağını biliyordum. Bir gün geri döneceğini hissediyordum. Ve işte, o gün geldi.";
			link.l1 = "Hakkını vermek lazım – planını kurnazlıkla uyguladı.";
			link.l1.go = "OS_Tavern3_4";
		break;

		case "OS_Tavern3_4":
			dialog.text = "Bir dakika! Fıçıdan nasıl haberi oldu ki? Sanırım... sanırım anlamaya başlıyorum! Garson kız! Bu yüzden selam bile vermeden, yangından kaçar gibi kaçtı. Demek ki Jack'le işini hallettiğini duymuş. Şimdi her şey yerine oturuyor. Kaptan, size minnettarım, size borcumu asla ödeyemem, siz...";
			link.l1 = "...";
			link.l1.go = "OS_Tavern3_5";
		break;
		
		case "OS_Tavern3_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_3");
			ChangeShowIntarface();
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Zaharia", "Marlow", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
			sld.name = GetCharacterName("Zachary");
			sld.lastname = GetCharacterName("Marlow");
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_tavern", "reload", "reload1");
			TeleportCharacterToPosAy(sld, -1.30, 0.00, -0.67, 1.50);
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "Zaharia_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
