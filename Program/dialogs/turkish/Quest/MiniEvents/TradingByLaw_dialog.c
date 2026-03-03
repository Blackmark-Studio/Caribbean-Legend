void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;

		case "Kristian":
			dialog.text = "Mütevazı yuvama hoş geldiniz! Ben Christian. Christian Deluce, hizmetinizdeyim. Sizi kapıma getiren nedir?";
			link.l1 = "Benim adım Kaptan "+GetFullName(pchar)+". Hatırı sayılır miktarda içki temin etmek istiyorum. Ne demek istediğim açık, değil mi?";
			link.l1.go = "Kristian_2";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_2":
			dialog.text = "Ne??? Kim böyle yalanlar yayar ki? Büyük bir yanlış anlaşılma bu, size temin ederim! Hiçbir tür içkiyle işim olmaz!";
			link.l1 = "Pekala, pekala... Görünen o ki, tam da aradığım kişiyi bulmuşum.";
			link.l1.go = "Kristian_3";
		break;

		case "Kristian_3":
			dialog.text = "Aman Tanrım, hayır-hayır-hayır! Ne suçlamalar bunlar! İçki ticareti mi? Ben mi? Ben... ben sadece, şey, yani... Pekâlâ, elimde bazı içkiler var, ama hepsi tamamen yasal! Sadece özel vatandaşlar için, yani... kutlamalar ve küçük toplumsal toplantılar için içecek temin ediyorum!";
			link.l1 = "Neden böyle titriyorsun, iyi adam? Ben buraya zindancı olarak değil, iyilik yapmak için geldim. Belki talihin döner, ben de bu işten birkaç doblon kazanırım.";
			link.l1.go = "Kristian_4";
		break;

		case "Kristian_4":
			dialog.text = "Ben mi? G-gergin? Saçmalık! Neden gergin olayım ki? Ben namuslu bir adamım - evim valinin konağının hemen dibinde! Şerefim üzerine, hiçbir yasayı çiğnemem!";
			link.l1 = "Yani içki ticaretine bulaşmadınız mı? Ne yazık, gerçekten büyük bir kayıp. Size hatırı sayılır bir kazanç fırsatıyla gelmiştim. Öyle altınlar ki, sıradan bir gizli tüccarın hayal bile edemeyeceği cinsten. Ama madem aradığım kişi siz değilsiniz, sizi daha fazla rahatsız etmeyeyim ve yoluma devam edeyim. Tabii... belki de...?";
			link.l1.go = "Kristian_5";
		break;
		
		case "Kristian_5":
			dialog.text = "Ah... bir dakika bekle... "+GetAddress_Form(NPChar)+"... affedersiniz, fırtınadaki martılar gibi aklım dağıldı, sizin saygın adınızı tamamen unuttum.";
			link.l1 = "Kaptan "+GetFullName(pchar)+".";
			link.l1.go = "Kristian_6";
		break;

		case "Kristian_6":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" "+pchar.lastname+", doğrusu, ben... yani... aradığınız kişinin nerede olduğunu biliyor olabilirim. Bu kişiye... cömert teklifinizi iletebilirim.";
			link.l1 = "Posta mı? Şaka yapıyor olmalısınız. Gerçekten bu kadar hassas bir meseleyi gereksiz ellere teslim etmem gerektiğine inanıyor musunuz?";
			link.l1.go = "Kristian_7";
		break;

		case "Kristian_7":
			dialog.text = "Doğru söylüyorsun. Ama... Tanrı yardımcım olsun... artık geri dönüş yok... evet, gerçekten de senin adamınım.";
			link.l1 = "Şimdi birbirimizi anladık, Christian. Meyhane ciddi bir içki sıkıntısı yaşıyor ve inanıyorum ki bu durumdan ikimiz de epeyce kazançlı çıkabiliriz.";
			link.l1.go = "Kristian_8";
		break;

		case "Kristian_8":
			dialog.text = "Kaptan, meyhanecinin dertlerine yabancı değilim. İnsanlar kapıma akın ediyor, bu da beni kendi küçük işimi sürdürmekten korkutur oldu – artık çok fazla göz üzerimde. Belki de siz... yani, sizin gibi saygın biri...";
			link.l1 = "Neden mallarını kendin han sahibine götürmüyorsun?";
			link.l1.go = "Kristian_9";
		break;

		case "Kristian_9":
			dialog.text = "O... benimle iş yapmaktansa bir cüzamlıya sarılmayı tercih ederdi. O kendini beğenmiş ahmak, benim gibi mütevazı tüccarlara sadece küçümsemeyle bakıyor.";
			link.l1 = "Gerçekten de, ünü ondan önce gelir. Sunduğun şeyleri doğrudan küçümseyebilir. Ama benim aracılığımla sunulursa - işte o bambaşka bir mesele.";
			link.l1.go = "Kristian_10";
		break;

		case "Kristian_10":
			dialog.text = "Arabulucu olmayı sen mi teklif ediyorsun? Bu düzenleme bana oldukça uygun görünüyor... Yakın zamanda olağanüstü büyüklükte bir sevkiyat aldık - daha önce hiç bu kadar miktarı başaramamıştık! Mahzenlerim en az yarım yıl dolu kalırdı. Ama Yüce Tanrı'nın lütfuyla, kıl payı yakalanmaktan kurtulduk\nHâlâ valinin ağına nasıl takılmadığımıza akıl erdiremiyorum. Böyle bir riski ikinci kez almak, resmen kendi sonumuzu hazırlamak olurdu.";
			link.l1 = "O halde belki de ışığa adım atmanın zamanı gelmiştir. Tamamen değil tabii, ama işlerini daha az tehlikeyle yürütecek kadar.";
			link.l1.go = "Kristian_11";
		break;

		case "Kristian_11":
			dialog.text = "I-ışığa adım atmak mı? Ama... neden, bunun için güçlü dostlar gerekir! Ve hatırı sayılır bir servet! Ne amaçla? Sen, kendi gemisi olan bir deniz kaptanı olarak, gerçekten demir atıp sonsuza dek bir meyhaneye mal mı tedarik edeceksin?";
			link.l1 = "Bağlantılar konusunda, benim etkim seninkinin ulaşamadığı yerlere uzanır. Paraya gelince... yatırım fazla olmayacaktır. Son endişene gelince - merak etme. Bu işlerde benim temsilcim olacaksın. Ben senin kalkanın olacağım, sen de benim güvenilir kaynağım. Anlaşmamız uzun ömürlü ve karşılıklı kârlı olacak. Sen düzenli müşteri kazanacaksın, ben ise güvenilir mal bulacağım. Böyle bir ortaklık kulağına nasıl geliyor?";
			link.l1.go = "Kristian_12";
		break;

		case "Kristian_12":
			dialog.text = "Bunun karmaşık bir tuzak olduğuna emindim. Fakat doğrusu, teklifiniz... gerçekten de fazlasıyla cazip geliyor. İstikrar, güvenilirlik... Böyle bir şansın bana güleceğini asla hayal etmemiştim. "+GetSexPhrase("Monsieur","Mademoiselle")+", tüm kalbimle katılıyorum! Ne kadar almak istiyorsunuz?";
			link.l1 = "Önce ticaretinizi sağlam temellere oturtalım, sonra ayrıntıları konuşuruz. Şu anda kilerinizde ne kadar rom ve şarap var?";
			link.l1.go = "Kristian_13";
		break;

		case "Kristian_13":
			dialog.text = "Şu anda mı? Ah... Belki de mahzenimi incelemeliyiz, orada envanterimi tam olarak gösterebilirim.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_GoToPogreb");	// спускаемся в погреб
		break;
		
		// погреб
		case "Kristian_15":
			dialog.text = "Bakalım... Ne hazineler var aşağıda? Ah, evet\nŞu anki stoğumda tam olarak yüz şişe kaliteli rom ve yüz şişe enfes şarap var.";
			link.l1 = "Bence bu iyi bir başlangıç. İthalat sorunlarınızı çözdükten sonra, her ay bu teslimatları aksatmadan sürdürebilir misiniz?";
			link.l1.go = "Kristian_16";
		break;

		case "Kristian_16":
			dialog.text = "Elbette, Kaptan! Hayır, ben bunu üç değil, hayır hayır... dört katı kadar bile halledebilirim! Hiçbir gecikme yaşamazsınız – her zaman bolca stok tutarım, böylece herhangi bir talihsizlik yaşansa bile tedarikiniz asla aksamaz.";
			link.l1 = "Bu yük için fiyatını söyle.";
			link.l1.go = "Kristian_17";
		break;

		case "Kristian_17":
			dialog.text = "Adil bir ödeme olarak şunu düşünürdüm: on şişe şarap için on dublon ve on şişe rom için üç dublon. Yani, tüm yük için toplamda yüz otuz dublon.";
			link.l1 = "Pekâlâ. Han sahibiyle konuşup hemen döneceğim.";
			link.l1.go = "Kristian_18";
		break;
		
		case "Kristian_18":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_18_1";
			pchar.questTemp.TPZ_Tavern_2 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			AddQuestRecord("TPZ", "4");
		break;
		
		case "Kristian_18_1":
			dialog.text = "Kaptan, ne haber? Meyhane sahibiyle konuşmanız nasıl geçti?";
			link.l1 = "Henüz onunla konuşmadım. O, sıradaki durağım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_18_1";
		break;

		case "Kristian_21":
			dialog.text = "Nasıl geçti, Kaptan? Meyhane sahibiyle anlaşmaya varabildiniz mi?";
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				link.l1 = "Harika iş çıkardım, Christian. Bunu ve sonraki tüm sevkiyatları iki yüz kırk dublona alacak. İlk parti için, istediğin yüz otuzunu sana ödeyeceğim, kalanını ise ödülüm olarak alacağım. Ancak, bundan sonraki kazançlar tamamen senin olacak.";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				link.l1 = "İyi iş çıkardım, Christian. Bunu ve sonraki sevkiyatları iki yüz dublona satın alacak. İlk sevkiyat için istediğin yüz otuz dublonu sana ödeyeceğim, aradaki farkı ise hak ettiğim bir ücret olarak alacağım. Bundan sonraki tüm kazançlar ise tamamen senin olacak.";
			}
			link.l1.go = "Kristian_22";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_22":
			dialog.text = "Bu inanılmaz bir haber, Kaptan! Böyle bir anlaşmayı hayal bile edemezdim - teşekkür ederim! Ama... belki de fazla acele ettiniz? Vali... ben... yani...";
			link.l1 = "Vali bunun gayet farkında. Bundan sonra, her ay yüz dublon ödeyecek ve düzgün ticaret raporları sunacaksın.";
			link.l1.go = "Kristian_23";
		break;

		case "Kristian_23":
			dialog.text = "İnanılmaz! Bunu nasıl başardınız, Kaptan? Vali sert bir adamdır ve karaborsacılara karşı amansız bir düşmandır...";
			link.l1 = "İşte mesele bu, Christian - o yasadışı ticarete karşı, dürüst işlere değil. Beni dinledi ve adada içki ticareti için açık şartlar koydu. Artık benim adımla iş yapacaksın. Herhangi bir yanlışta, senin kadar ben de sorumluyum. O yüzden beni hayal kırıklığına uğratma, yoksa öteki dünyada bile seni bulurum.";
			link.l1.go = "Kristian_24";
		break;

		case "Kristian_24":
			dialog.text = "Yemin ederim, Kaptan, buna pişman olmayacaksınız!";
			link.l1 = "Şimdi meyhaneciyle işleri sonuçlandırmalıyız, ardından anlaşmamızın ayrıntılarını hallederiz.";
			link.l1.go = "Kristian_25";
		break;
		
		case "Kristian_25":
			dialog.text = "Elbette, Kaptan. Yükü hemen teslim almaya hazır mısınız? Bunun ücreti yüz otuz dublon.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Evet, işte altınlarınız.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Şu anda gerekli paraya sahip değilim. Burada kal — ödemeyle geri döneceğim.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_25_1":
			dialog.text = "Kaptan! Malları almaya geri mi döndünüz? Fiyat hâlâ yüz otuz dublon.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Elbette buldum! İşte ödemeniz.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Ne yazık ki, hâlâ param yok. Daha sonra tekrar uğrayacağım.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_26":
			dialog.text = "Çok teşekkürler! Alın bunları! Söz verdiğim gibi, yüz şişe şarap ve yüz şişe rom.";
			link.l1 = "Mürettebatım yükle ilgilenecek. Bu arada, ben de han sahibiyle konuşmam gerek.";
			link.l1.go = "Kristian_27";
			RemoveDublonsFromPCharTotal(130);
		break;
		
		case "Kristian_27":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.TPZ_Tavern_4 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "Kristian_31":
			dialog.text = ""+pchar.name+"! Ne çabuk döndünüz! Söyleyin, anlaşmamız istediğimiz gibi gitti mi?";
			link.l1 = "Her şey gayet güzel ilerledi, Christian. Meyhane sahibi, aynı miktarda içkiyi ayda iki kez isteyecek. Onun yerine düzenli olarak içki gönderirsen, yoksulluk nedir yakında unutursun.";
			link.l1.go = "Kristian_32";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_32":
			dialog.text = "Kaptan... siz... sanki kaderin kendisi sizi kapıma getirdi! Karşımda gerçek bir mucize gerçekleşti - şansımın bu kadar yaver gitmesine inanmakta zorlanıyorum! Böyle bir iyiliği hak etmek için ne yaptım? Minnettarlığımı kelimelerle anlatamam!";
			link.l1 = "Ben ise sana yardımcı olabilirim, Christian. Her ay, en iyi mallarından seçilmiş bir kısmını yalnızca bana ayıracaksın, başka hiç kimseye satmayacaksın. Bunları senin belirlediğin fiyatlardan alacağım - on şişe şarap için on dublon, on şişe rom için ise üç dublon ödeyeceğim.";
			link.l1.go = "Kristian_33";
		break;

		case "Kristian_33":
			dialog.text = "Bu benim için büyük bir zevk olur, "+pchar.name+", sizin özel temininiz için malları ayırmak üzere! Şerefim üzerine, asla sizi hayal kırıklığına uğratmam! Ne kadar istersiniz? Elli şişe mi? Belki yüz? Dilediğiniz miktarı söyleyin!";
			link.l1 = "Bu miktarlar şu anki ihtiyaçlarımı aşıyor. Her birinden yirmişer şişe fazlasıyla yeterli olacaktır. İhtiyacım artarsa - derhal haberdar edilirsiniz.";
			link.l1.go = "Kristian_34";
		break;

		case "Kristian_34":
			dialog.text = "Elbette, elbette! O halde anlaştık - yirmi şişe şarap ve yirmi şişe rom, toplamda yirmi altı dublon karşılığında. Her ayın on beşinci günü, mallarınız sizi bekliyor olacak. Ne zaman uğramak isterseniz, sizi memnuniyetle karşılarım; ister sadece birkaç hoş söz etmek için gelmiş olun!";
			link.l1 = "Harika! Son olarak bir konuya daha vurgu yapmam gerek, Christian. Dürüstlüğün için kendi itibarımı ortaya koydum. Beni hayal kırıklığına uğratma, yoksa sonuçlarına katlanırsın.";
			link.l1.go = "Kristian_35";
		break;

		case "Kristian_35":
			dialog.text = "Ben... ne önerirsiniz, kaptan... elbette siz... hayır-hayır, asla sizi hayal kırıklığına uğratmam! Her şey kusursuz bir nezaketle yürütülecek, ruhum üzerine yemin ederim!";
			link.l1 = "O halde yollarımız tekrar kesişene dek!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_SpawnShip");
		break;
		
		case "Pirate_1":
			dialog.text = "Sen karışan "+GetSexPhrase("cur","fahişe")+"! Sana hiç kendi işin olmayan meselelere burnunu sokmanın başına dertten başka bir şey getirmeyeceği öğretilmedi mi?";
			link.l1 = "Benim gemime izinsiz saldıran sendin, şimdi de beni karışmakla mı suçluyorsun? Yoksa aklını büsbütün mi yitirdin?";
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			dialog.text = "Yıldırım direğimi parçalasa da! Demek sen, "+GetSexPhrase("sefil velet","değersiz fahişe")+",   kendini bulaştırdığın işlerden en ufak bir fikrin yok mu? Meyhanenin erzaklarının öylece tesadüfen kaybolduğunu mu sandın?";
			link.l1 = " O içki fabrikasını kül edenin sen olduğunu mu söylüyorsun? ";
			link.l1.go = "Pirate_3";
		break;

		case "Pirate_3":
			dialog.text = "Ha-ha, sonunda gerçek kalın kafana işledi, zincir gülleler bağırsaklarımı delip geçsin! Evet, bunu yapan bendim! O tedarikçi ticarette kök salmıştı. Ama gördüğün gibi, rakiplerimi asla alt etmeden bırakmam. Ve sen de onların kaderini paylaşacaksın, saçma gülleler yelkenlerimi paramparça etsin!";
			link.l1 = "Çok eğlenceli. O halde, yeteneklerinin sınırını görelim, Neptün’ün yaratıkları cesedini ziyafet sofrasına çevirsin! Ha-ha!";
			link.l1.go = "Pirate_4";
		break;
		
		case "Pirate_4":
			DialogExit();
			
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Kristian_41":
			dialog.text = "Selamlar, "+pchar.name+"! Hangi uğurlu rüzgarlar seni kapıma getirdi?";
			if(CheckAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom")) // торговля вином и ромом
			{
				if (GetDataDay() == 15)
				{
					link.l1 = "Günaydın, Christian. Mallarım hazır mı?";
					link.l1.go = "Kristian_42";
				}
			}
			link.l2 = "İyi günler, Christian. Sadece işlerinin yolunda gittiğinden emin olmak istedim. Şimdi seni daha fazla rahatsız etmeyeceğim.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Kristian_41";
		break;

		case "Kristian_42":
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				dialog.text = "Elbette, Kaptan! Çalışkanlığımdan en ufak bir şüpheniz olabilir mi?";
				if (PCharDublonsTotal() >= 130)
				{
					link.l1 = "Bir an bile düşünmedim, Christian. Anlaştığımız gibi, işte ödemen. Şimdi içkimi alacağım.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "Hiç de değil. Ne yazık ki, şu anda kesem fazlasıyla hafif. Daha iyi hazırlandığımda geri döneceğim.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			else
			{
				dialog.text = "Elbette, Kaptan! Çalışkanlığım konusunda en ufak bir şüpheniz olabilir mi?";
				if (PCharDublonsTotal() >= 26)
				{
					link.l1 = "Bir an bile düşünmedim, Christian. Anlaştığımız gibi işte doblonların. Şimdi içkilerimi alacağım.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "Hiçbir şekilde değil. Ne yazık ki, şu anda uygun bir ödeme yapacak durumda değilim. Cüzdanım yeterince dolduğunda geri döneceğim.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoBlock")) // увеличить объём поставок вина и рома
			{
				link.l4 = "Christian, aylık siparişimi artırmak istiyorum. Tam olarak her ay yüz şişe rom ve yüz şişe şarap.";
				link.l4.go = "UpgradeVino";
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom") && sti(pchar.Money) >= 50000) // увеличить объём поставок вина и рома, если в первый раз не принесли
			{
				link.l4 = "Christian, anlaşmamızı genişletmeyi yeniden düşünmek istiyorum.";
				link.l4.go = "UpgradeVino_Agreed";
			}
		break;
		
		case "Kristian_43":
			dialog.text = "Harika. Her zamanki gibi, taze mallarınız on beşinde sizi bekliyor olacak. Bir sonraki ziyaretinizi sabırsızlıkla bekliyorum.";
			link.l1 = "Dönüşüme güvenebilirsiniz. Yollarımız tekrar kesişene dek.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				RemoveDublonsFromPCharTotal(130);
				AddItems(pchar, "potionrum", 100);
				AddItems(pchar, "potionwine", 100);
			}
			else
			{
				RemoveDublonsFromPCharTotal(26);
				AddItems(pchar, "potionrum", 20);
				AddItems(pchar, "potionwine", 20);
			}
			
			DeleteAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom");
			SetFunctionTimerCondition("TPZ_KristianReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			pchar.questTemp.TPZ_KritstianVinoAndRom = sti(pchar.questTemp.TPZ_KritstianVinoAndRom) + 1; // счётчик покупок
		break;

		case "UpgradeVino":
			dialog.text = "Kaptan, böyle bir genişleme iş için çok faydalı olurdu, ama bunun da hatırı sayılır bir maliyeti var! Daha fazla mal, ek işçi, daha büyük depolar, daha geniş gemiler kiralamak gerektirir... Gerekli yatırım olmadan, bu kadar büyük siparişlerin zamanında teslimatını asla garanti edemem.";
			link.l1 = "Böyle bir düzenleme için ne kadar bir meblağ gerekir? Bu büyütülmüş girişimin sorunsuz işlemesi için ne kadar yatırım yapmak gerekir?";
			link.l1.go = "UpgradeVino_2";
		break;

		case "UpgradeVino_2":
			dialog.text = "Elli bin peso yeterli olur. Bundan sonraki masrafları kendi cebimden karşılarım.";
			link.l1 = "Elli bin mi? Doğrusu... bu hiç de az bir para değil. Daha mütevazı bir bütçeyle idare edemez misin gerçekten?";
			link.l1.go = "UpgradeVino_3";
		break;

		case "UpgradeVino_3":
			dialog.text = "Derin bir üzüntüyle söylüyorum Kaptan, bu miktarın kesinlikle en alt sınır olduğunu belirtmek zorundayım. Eğer işin kolayına kaçılırsa, girişimimiz... nasıl desem, felaketle sonuçlanabilir. Böyle bir felaketin ne sizin çıkarınıza ne de benimkine hizmet edeceğini söyleyebilirim.";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "İşte ödemenin tamamı. Böyle bir güvene layık olduğunu göster, Hristiyan.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Daha fazla düşündüm Christian, bu genişleme biraz erken olabilir. Koşullar daha elverişli olduğunda bu konuyu tekrar ele alalım.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_4":
			dialog.text = "Dediğiniz gibi, Kaptan. Fikriniz değişirse, hizmetinizde olmaya devam edeceğim.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			pchar.questTemp.TPZ_KritstianVinoPotom = true;
		break;
		
		case "UpgradeVino_Agreed":
			dialog.text = "Kaptan, harika haberlerim var! Elli bin gümüşü getirdiniz mi, hemen devam edebilir miyiz?";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "İşte ödemenin tamamı. Böyle bir güvene layık olduğunu göster, Christian.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Şu anda kasamda gerekli miktarda para yok. Mali durumum elverdiğinde geri döneceğim.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_5":
			dialog.text = "Şerefim üzerine, "+pchar.name+", bu kararınızdan asla pişman olmayacaksınız! Hazırlıklara derhal başlayacağım. Bir sonraki teslimatınızdan itibaren, yüz şişe en kaliteli rom ve aynı miktarda mükemmel şarap alabilirsiniz, hepsi tam bir sevkiyat için yüz otuz doblon karşılığında.";
			link.l1 = "Çok memnun oldum. Ama unutmayın – her konuda en yüksek gizliliği koruyun. Davranışlarınız, bu sulardaki itibarımı doğrudan etkiler.";
			link.l1.go = "UpgradeVino_6";
			AddMoneyToCharacter(pchar, -50000);
		break;
		
		case "UpgradeVino_6":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_41";
			pchar.questTemp.TPZ_UpgradeVino = true;
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			DeleteAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom");
			AddQuestRecordInfo("Useful_Acquaintances", "4_1");
		break;
		
		
	}
}