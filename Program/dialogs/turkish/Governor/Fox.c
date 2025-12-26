// полковник Фокс - бравый командир морской пехоты 'морские лисы'.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyReward"))
			{
				dialog.text = "Ne istiyorsunuz, efendim? Aman... bir dakika! Siz, kızımı Levasseur'un pis uşaklarının elinden kurtaran Fransız kaptansınız! ";
				link.l1 = "Catherine'ın sana benden çoktan bahsettiğini görüyorum...";
				link.l1.go = "terrapin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Usurer") && !CheckAttribute(npchar, "quest.utensil"))
			{
				dialog.text = "Ne istiyorsunuz, efendim?";
				link.l1 = "Günaydın, Albay. Size biraz 'alışılmadık' bir meseleyle geldim. Bana biraz zaman ayırabilir misiniz?";
				link.l1.go = "guardoftruth";
				break;
			}
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "eng_reward")
			{
				dialog.text = "Eğer yanılmıyorsam, sizsiniz "+GetSexPhrase("kaptan","bayan kaptan")+" Sint Maarten'daki görevi adamlarımla birlikte yerine getirmeme kim yardım etti? "+TimeGreeting()+"!";
				link.l1 = TimeGreeting()+", Albay. Evet, o benim.";
				link.l1.go = "FMQN";
				break;
			}
			dialog.text = "Ne istiyorsunuz, efendim?";
			link.l1 = "Bir şey yok, Albay. Müsaadenizle ayrılıyorum.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guardoftruth":
			dialog.text = "O halde, madem bu kadar geldin, dökül bakalım...";
			link.l1 = "Kısa süre önce Rollie the Cap adlı Hollandalı bir korsanın komutasındaki bir şalopaya çıktınız ve kaptanı buraya, St. John's'a getirdiniz.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Kaptan mı? Hadi ama, güldürmeyin beni! Bu suçlu pisliğin bu onurlu unvanı taşımaya hakkı yok. Ben bir lanet korsanı, bir kurt sürüsünün başını yakaladım; İngiliz tüccarlarını ve tacirlerini soymuş ve öldürmüş biri bu. Ve ben de onun ve yandaşlarının hak ettiklerini bulmasını sağladım – tüm St. John’s, iskelede asılışlarını izledi!";
			link.l1 = "Sanırım artık bu alçağı sorgulama şansım kalmadı... Albay, belki siz bana yardımcı olabilirsiniz? Korsanın üzerinde ona ait olmayan bir şey vardı – altın buhurdan. Üzerinde buna benzeyen bir şey buldunuz mu?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Hayır, onu aradık ve o alçağın üstünde hiçbir eşyası yoktu. Üstelik, sahip olduğu her şeyi de mutlaka dürüst tüccarlardan çalmıştır! Endişene gelince... hmm, hayır, onu bulamadık. Bir tütsülük korsan gemisinde ne işe yarar ki? Gerçekten aralarında bir rahip olduğunu mu düşünüyorsun?";
			link.l1 = "Hayır, bilmiyorum. Rollie the Cap onu Willemstad’daki tefeciden aldı, o da başka bir korsandan almış. Tütsülük sağlam ve değerli, ben de onu gerçek sahiplerine geri vermeye çalışıyorum. Sanırım Rollie, saksağan gibi ona göz koymuştu.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Gerçek şu ki, Rollie'nin gemisine çıktığımızda ambarları boştı ve birkaç sandıkta sadece birkaç dublon vardı. Tam anlamıyla çer çöp. Ne değerli bir şey, ne de altın bir buhurdan. Bir korsana hiç yakışmayan böyle bir eşyayı kesinlikle hatırlardım.\nSanırım o lanet korsan, birikimlerini Dominika'da sakladı. Oraya çıktık, etrafı aradık ama hiçbir şey bulamadık. Fakat adada kalmadık ve iç kısımlarını da keşfetmedik, çünkü orada çok fazla yabanî vardı.";
			link.l1 = "Hm... Korsan, çaldığı diğer eşyalarla birlikte tütsülüğü Dominika'da bir yere saklamış olabilir... Ne yazık. Korsanı idamdan önce sorguladınız mı?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Yaptım... ama yüzüme karşı gülmeye başladı. Ama onun sakladığı şeyler umurumda değildi. Rollie the Cap idam edildi ve en önemlisi de bu.";
			link.l1 = "Anladım. Hikayeniz ve zamanınız için teşekkürler, Albay. Hoşça kalın...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("GuardOT_Fox_DlgExit");
		break;
		
		case "terrapin":
			dialog.text = "Birkaç kez, kaptan! Böylesine onurlu ve cesur bir davranışı bir Fransızdan beklemek zordu. Size hem bir asker hem de bir baba olarak minnettarım. Bu dünyada benim için kızımdan daha değerli hiçbir şey yok...";
			link.l1 = "Yardımcı olabildiğim için memnunum ve umarım zamanla yaptıklarım Fransızlara bakışınızı değiştirir.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Böylesine onurlu ve cömert bir centilmenin, hayatını tanımadığı bir İngiliz kız için riske atan sizin gibi birinin varlığı, sizin milletinize karşı hislerimin önemli ölçüde yumuşamasına sebep olacak!";
			link.l1 = "Her milletten farelerin arasında bile dürüst insanlar bulunur, albay...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Ve bunu kanıtladınız! Bir ödül sizi bekliyor, kaptan. Elbette bir kızın hayatı paha biçilemez, ama Jonathan Fox borcunu her zaman öder, buna yemin ederim! Siz gerçek bir askersiniz, bu yüzden size vereceğim hediye de bir askerin hediyesi olacak. Buyurun, bakın.\nBu bir blunderbuss, mükemmel bir donanma tüfeği ve tek elle kullanılabiliyor. Özel cıvatalarla doldurulabilir, en sağlam zırhı bile deler. Ayrıca saçma atar ve sağlam yapısı sayesinde içine çivi de doldurabilirsiniz. Alın, artık sizin.";
			link.l1 = "Böyle harika bir hediye için teşekkür ederim, Albay!";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			Log_Info("You have received a blunderbuss");
			Log_Info("You have received 10 arrows");
			Log_Info("You have received 10 charges of nails");
			Log_Info("You have received instructions for creating the harpoon arrows");
			Log_Info("You have received instructions for creating the charge of nails");
			GiveItem2Character(pchar, "pistol8");
			TakeNItems(pchar, "harpoon", 10);
			TakeNItems(pchar, "GunEchin", 10);
			GiveItem2Character(pchar, "recipe_harpoon"); 
			GiveItem2Character(pchar, "recipe_GunEchin"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "Sana ayrıca küçük bir miktar cephane ve bunların nasıl yapılacağına dair talimatlar da veriyorum. Gücünü tam anlamıyla kullanmaman yazık olurdu!";
			link.l1 = "Teşekkür ederim, Albay. Böyle bir hediyeyi geri çevirmem, ama şunu bilmenizi isterim ki Catherine’i ödül için kurtarmadım. Savunmasız bir kızın zarar görmesine göz yumamazdım.";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "Bunu biliyorum, kaptan. Bu, size iki kat onur kazandırıyor. Catherine gerçekten sizden etkilendi ve ona iyi bir izlenim bırakmak hiç de kolay değildir. Onu kurtardığınız için size bir kez daha minnettarız. Ben de size borçluyum!";
			link.l1 = "Teşekkür ederim bu hediye için, Albay. Catherine’e en iyi dileklerimi iletin ve keşke bir dahaki sefere babasını dinlese.";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Elbette, Kaptan! Hoşça kalın, yolunuz açık olsun!";
			link.l1 = "Elveda, Albay.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Terrapin_KathyReward");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
			ChangeCharacterNationReputation(pchar, ENGLAND, 20);
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Raporu okudum. Yaptıkların çok değerli, bu yüzden ödüllendirilmelisin. Sefer hizmetlerin için otuz bin peso ve askerlikte gösterdiğin kahramanlık için silahlar. Bu kılıcı ve bu tüfeği kabul et. Artık hepsi senin!";
			link.l1 = "Teşekkür ederim, efendim.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Elbette, Kaptan. Ayrıca, İngiliz kolonilerinin, yetkililerin ve şahsen benim sevgi ve saygımı da kazandınız. Adamlarımı yalnız bırakmadığınız ve onlara görevlerinde yardımcı olduğunuz için teşekkür ederim!";
			link.l1 = "Memnuniyetle, Albay...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "Şimdi, lütfen beni mazur görün - ilgilenmem gereken başka işlerim var. Yolun açık olsun, Kaptan "+pchar.lastname+".";
			link.l1 = "Elveda, "+GetAddress_Form(NPChar)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
