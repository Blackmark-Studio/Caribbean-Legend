void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "AlonsoNaPalube":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube"))
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube2 = true;
				dialog.text = "Kararınız nedir, Kaptan? Belki de yapmamalıyız?";
				link.l1 = "Görev için daha fazla gönüllü toplamayı başardın mı?";
				link.l1.go = "AlonsoNaPalube_StrongGroup";
			}
			else
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube = true;
				dialog.text = "Kaptan, bir dakika.";
				link.l1 = "Rapor ver, Alonso.";
				link.l1.go = "AlonsoNaPalube_2";
			}
			locCameraFromToPos(-10.33, 9.69, -22.16, true, -5.22, 7.19, -21.06);
		break;
		
		case "AlonsoNaPalube_2":
			dialog.text = "Mürettebat Cayman için ne planladığını merak ediyor. İnsanlar endişeli.";
			link.l1 = "Henüz karar vermedim. Peki, adamlar neden endişeli Alonso?";
			link.l1.go = "AlonsoNaPalube_3";
		break;
		
		case "AlonsoNaPalube_3":
			dialog.text = "Bu ada Kaptan Blackwood'un hükümranlığı. Denizciler, adayı baştan sona deli gibi kazdığını söylüyor. Kazılarında onlarca adamı mahvetmiş... Ve ondan ayrılanlar... tuhaf hikayeler anlatıyor.";
			link.l1 = "Ne tür hikayeler?";
			link.l1.go = "AlonsoNaPalube_4";
		break;
		
		case "AlonsoNaPalube_4":
			dialog.text = "Blackwood artık eskisi gibi biri değil. Bir fatihin hazinesini bulmaya takıntılı hale gelmiş. Bunun için her şeyi ve herkesi feda etmeye hazır. Güzel hikayelere karışmayı, tek başına karaya çıkıp tuzaklara düşmeyi ne kadar sevdiğini biliyoruz... Ama bu sefer paçayı kurtaramayacaksın.";
			link.l1 = "Rapor ve uyarı için teşekkürler. Karaya çıkmaya karar verirsem, öncü birlikle ve en iyi savaşçılarımızdan bir grupla gideceğimden emin olabilirsin.";
			link.l1.go = "AlonsoNaPalube_5";
		break;
		
		case "AlonsoNaPalube_5":
			dialog.text = "Bu zor olabilir, Kaptan. Gemiye çıkmak bir şey, ama Blackwood'un Küçük Antiller'in her köşesinden topladığı serserilerin kılıçları ve denizcilerin kurşunları altında karaya ayak basmak bambaşka bir iş. Üstelik Cayman hakkında kötü söylentiler dolaşıyor... Hayır, böyle bir iş için gönüllü bulmak kolay olmayacak.";
			link.l1 = "O zaman elimizden gelenle idare edeceğiz. Katılımın zorunlu, Alonso.";
			link.l1.go = "AlonsoNaPalube_LiteGroup";
			link.l2 = "Bence, kanıtlanabilecek her şeyi herkese zaten kanıtladım. İyi dövüşçüler ve nişancılar gidecek. Bu bir emirdir.";
			link.l2.go = "AlonsoNaPalube_StrongGroup";
			link.l3 = "Hmm... Sanırım bunu iyice düşünmem gerek. Belki bu konuya sonra tekrar döneriz.";
			link.l3.go = "AlonsoNaPalube_Exit";
		break;
		
		case "AlonsoNaPalube_Exit":
			SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
			EndQuestMovie();
			bQuestDisableMapEnter = false;
			chrDisableReloadToLocation = false;
			if(UnloadLocation(loadedLocation) == true)
			{
				pchar.Ship.Pos.x = 0;
				pchar.Ship.Pos.z = 0;
				pchar.Ship.Ang.y = 0;
				Land_MapLoad();
				pchar.location = "";
			}
		break;
		
		case "AlonsoNaPalube_LiteGroup":
			dialog.text = "Pekâlâ, Kaptan!";
			link.l1 = "Blackwood'un gemisi ne olacak? Sorun çıkarmaz mı?";
			link.l1.go = "AlonsoNaPalube_Vpered";
			pchar.questTemp.LadyBeth_LiteGroup = true;
		break;
		
		case "AlonsoNaPalube_StrongGroup":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 40 || sti(pchar.rank) >= 12)
			{
				dialog.text = "Emredersiniz, Kaptan!";
				link.l1 = "Blackwood'un gemisi ne olacak? Sorun çıkarmaz mı?";
				link.l1.go = "AlonsoNaPalube_Vpered";
				pchar.questTemp.LadyBeth_StrongGroup = true;
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 40) Notification_Skill(true, 40, SKILL_LEADERSHIP);
				if (sti(pchar.rank) >= 12) Notification_Level(true, 12);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube2"))
				{
					dialog.text = "Henüz değil, Kaptan.";
				}
				else
				{
					dialog.text = "Bana ya da subaylarına kendini kanıtlaman gerekmiyor, nereye dersen oraya emrinle gideriz, ama sıradan denizciler böyle düşünmüyor. Korkarım sorunlar çıkacak, Kaptan.";
				}
				link.l1 = "O zaman elimizden gelenle yetinmek zorundayız. Katılımın zorunlu, Alonso.";
				link.l1.go = "AlonsoNaPalube_LiteGroup";
				link.l2 = "Hmm... Sanırım bunu iyice düşünmem gerek. Belki bu soruya sonra tekrar döneriz.";
				link.l2.go = "AlonsoNaPalube_Exit";
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 40) Notification_Skill(false, 40, SKILL_LEADERSHIP);
				if (sti(pchar.rank) < 12) Notification_Level(false, 12);
			}
		break;
		
		case "AlonsoNaPalube_Vpered":
			dialog.text = "Bir karakol gemisi. Gerçek bir güzellik, ama huysuz olduğu söylenir. Onun için endişelenmene gerek yok. Muhtemelen tüm mürettebat karada köle gibi çalışıyor, gemi ise kıyının girintilerinde güvenle saklanıyor. Eğer ve ne zaman kazanırsak, onu kıyıdan ödül olarak alabiliriz.";
			link.l1 = "Adamları topla. Bugün iyi bir gün - şans bizden yana olacak.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_AlonsoNaPalube_Vpered");
		break;
		
		// Диалог в таверне с Блеквудом
		case "LadyBeth_DialogInCity": // главное меню
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Fourth"))
			{
				dialog.text = "Seni görmek güzel, Kaptan. Sanırım her şeyi zaten konuştuk..";
				link.l1 = "Evet. Elveda.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LadyBeth_DialogInCity_again";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Third"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", "+npchar.name+"";
				link.l1.go = "LadyBeth_DialogInCity_Third_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", Kaptan Blackwood.";
				link.l1.go = "LadyBeth_DialogInCity_Second_1";
				break;
			}
			if (startHeroType == 4)
			{
				dialog.text = "...";
				link.l1 = "Merhaba. Siz Kaptan Blackwood musunuz?";
				link.l1.go = "LadyBeth_DialogInCity_First_Helena_1";
			}
			else
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+" . Sen Kaptan Albert Blackwood'sun, doğru mu?";
				link.l1.go = "LadyBeth_DialogInCity_First_1";
			}
		break;
		
		case "LadyBeth_DialogInCity_again": // повтор
			dialog.text = "Seni görmek güzel, Kaptan. Sanırım her şeyi zaten konuştuk.";
			link.l1 = "Gerçekten öyle. Hoşça kal.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LadyBeth_DialogInCity_again";
		break;
		
		case "LadyBeth_DialogInCity_First_1": // первый диалог
			dialog.text = "Evet, benim. Ya sen?";
			link.l1 = "Kaptan "+GetFullName(pchar)+". Gemiyi ben komuta ediyorum '"+PChar.Ship.Name+"'.";
			link.l1.go = "LadyBeth_DialogInCity_First_2";
		break;
		
		case "LadyBeth_DialogInCity_First_2":
			dialog.text = "Kaptan... Cayman'a gittiniz mi?";
			link.l1 = "Az önce uğradım.";
			link.l1.go = "LadyBeth_DialogInCity_First_3";
		break;
		
		case "LadyBeth_DialogInCity_First_3":
			dialog.text = "Oralarda hazineler hakkında bir şey duydun mu?";
			link.l1 = "Hayır, özel bir şey yok.";
			link.l1.go = "LadyBeth_DialogInCity_First_4";
		break;
		
		case "LadyBeth_DialogInCity_First_4":
			dialog.text = "İspanyollardan izler mi? Eski silahlar mı? Conquistadorlar zamanından kalma paralar mı?";
			link.l1 = "Buna benzer bir şey bulamadım.";
			link.l1.go = "LadyBeth_DialogInCity_First_5";
		break;
		
		case "LadyBeth_DialogInCity_First_5":
			dialog.text = "Yerel efsaneler mi? Cortez hakkında hikayeler? Gömülerle ilgili bir şeyler?";
			link.l1 = "Üzgünüm Kaptan, ama böyle bir bilgim yok. Ayrıca bu artık bir sorguya dönüşmeye başladı.";
			link.l1.go = "LadyBeth_DialogInCity_First_6";
		break;
		
		case "LadyBeth_DialogInCity_First_6":
			dialog.text = "Özür dilerim... Eski bir subayın kötü alışkanlığı. Sadece... bu benim için gerçekten çok önemli.";
			link.l1 = "Neden özellikle Cayman ile bu kadar ilgileniyorsun?";
			link.l1.go = "LadyBeth_DialogInCity_First_7";
		break;
		
		case "LadyBeth_DialogInCity_First_7":
			dialog.text = "Önemli değil. Bir kez daha özür dilerim.";
			link.l1 = "Anladım. Arayışlarında bol şans.";
			link.l1.go = "LadyBeth_DialogInCity_First_8";
		break;
		
		case "LadyBeth_DialogInCity_First_8":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Good night";
			else sStr = "Wishing you a good day";
			dialog.text = "Eğer değerli bir şey bulursan, yanıma gel. Başka bir kaptanla... denizi anlayan biriyle sohbet etmek hoşuma giderdi. "+sStr+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_First_9";
		break;
		
		case "LadyBeth_DialogInCity_First_9":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_1": // первый диалог с Элен
			dialog.text = "Karşımda canlı kanlısın. Ve sen... Kaptan Helen MacArthur? Jan Svenson'un gözdesi, değil mi? Senin hakkında çok şey duydum.";
			link.l1 = "İyi bilgilendirilmişsiniz, Kaptan Blackwood. Ama bir İngiliz subayının benim hakkımda bilgi sahibi olmasına şaşırmadım.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_2":
			dialog.text = "Eski bir subay. Ve tüm kırmızı ceketliler senin ve... Taç’tan aldığın kendine has ayrıcalıklarını biliyor. Söylediklerine göre, demir ağacı kokmazmış. Ayrıca baban Sean MacArthur’un seni çocukluğundan beri denize çıkardığı ve sonunda kaptan yaptığı hikaye filoda adeta bir efsaneye dönüştü.";
			link.l1 = "Ve bu efsaneyle tanışmak nasıl bir his?";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_3";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_3":
			dialog.text = "Ben şahsen etkilendim. Ancak itiraf etmeliyim ki, eski meslektaşlarımın birçoğu bunu oldukça sinir bozucu buluyor. Ama kaptan olmak için soylu bir aileden gelmek ya da kraliyet fermanı almak yetmiyor, değil mi?";
			link.l1 = "Doğru. Bilgi, tecrübe ve yetkinliğini sürekli kanıtlama isteği gerekir. Özellikle de benim durumumda.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_4";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_4":
			dialog.text = "Kesinlikle! Denizde de, hayatta da önemli olan unvanlar değil, sonuçlardır. Sizinle tanıştığıma memnun oldum, Kaptan MacArthur. Umarım tekrar karşılaşırız. Belki seferimden döndüğümde bir kadeh şarap içmek için uğrarsınız?";
			link.l1 = "Belki. Aramalarınızda bol şans, Kaptan.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_5_harizma";
			link.l2 = "İlgilenmiyorum. Ama arayışlarında bol şans, Kaptan.";
			link.l2.go = "LadyBeth_DialogInCity_First_Helena_5_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_harizma":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_oruzhie":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_1": // второй диалог
			dialog.text = "Ah, Kaptan "+pchar.lastname+"! Seni görmek ne güzel. Oturmak ister misin?";
			link.l1 = "Memnuniyetle.";
			link.l1.go = "LadyBeth_DialogInCity_Second_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_2":
			dialog.text = "Kaptan... söyle bana, gerçek hazineler senin için ne ifade ediyor?";
			link.l1 = "Gerçek hazine aşktır. Yanında doğru insanın olması. Yalnız kalmaktan daha kötü bir şey yok.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love";
			link.l2 = "Para, elbette. Hazine başka ne olabilir ki?";
			link.l2.go = "LadyBeth_DialogInCity_Second_3_sokrovisha";
			link.l3 = "Değerli ve eşsiz ekipmanlar. İyi bir kılıç ya da tabanca, altından daha değerlidir.";
			link.l3.go = "LadyBeth_DialogInCity_Second_3_oruzhie";
			link.l4 = "Bilgi. En değerli hazine kafanın içindekidir.";
			link.l4.go = "LadyBeth_DialogInCity_Second_3_znania";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love":
			if (startHeroType == 4)
			{
				dialog.text = "Aşk mı? Hmm... Bir korsanın kızından böyle bir cevap beklemezdim. Ben... Ben nişanlıydım. Elizabeth'le. Barbadoslu bir plantasyon sahibinin kızıydı. Ama babası... benim yeterince param olmadığını düşündü. Ona sevgimden başka ne sunabilirdim ki? Şanslıydın, Kaptan MacArthur. Baban yeteneklerini çeyizinden daha çok değerli bulmuş.";
				link.l1 = "Belki de mesele şans değil, gerçek aşkın altınla ölçülmemesinde. Babam bunu anlamıştı. Peki ya nişanlın? O da babasının görüşlerini paylaşıyor mu?";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_1";
			}
			else
			{
				dialog.text = "Aşk mı? Evet... Belki de haklısın. Ben... nişanlıydım. Barbados'ta. Birbirimizi seviyorduk ama... babası beni layık görmedi. Ha! Yeterince zengin değilmişim. İşte bu yüzden buradayım - hepsinin yanıldığını kanıtlayacak hazineleri arıyorum. Belki de boşuna?";
				link.l1 = "Belki de onunla konuşmalısın? O plantasyon sahibini boş ver.";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_2";
			}
			AddComplexLandExpToScill(100, 100, 0);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_2":
			dialog.text = "Konuşmak... Evet, belki. Ama ne söyleyeceğim ki? 'Üzgünüm, sana düzgün bir hayat sunamadım' mı diyeceğim? Hayır. Kazanan olarak dönmeliyim. Ya da hiç dönmemeliyim.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_1":
			dialog.text = "Elizabeth? Hayır... o beni seviyor. Ama ben... onun yoksulluk içinde yaşamasına izin veremezdim. O daha iyisini hak ediyor. Ve ona layık olduğumu kanıtlamalıyım.";
			link.l1 = "Bazen gurur, yoksulluktan daha çok mutluluğun önüne geçer, Kaptan.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_2":
			dialog.text = "Boş elle dönemem. Yapamam. Özür dilerim, çok işim var. Seninle sohbet etmek güzeldi, Kaptan MacArthur.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha":
			dialog.text = "Ne kadar sıradan bir cevap. Ama tartışmak zor. Gerçekten de, Bristol'un kenar mahallelerinde büyüdüğünde, yiyecek artıklar için bile savaşmak zorunda kaldığında... paranın gerçek değerini anlamaya başlıyorsun. Lüks değil bu. Özgürlük. O pislikten, büyük zorluklarla tırmanıp çıktığın yere bir daha asla dönmeme imkânı.";
			link.l1 = "Katılıyorum. Para çoğu sorunu çözer. Eğer çözmüyorsa - demek ki yeterince yok demektir.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_sokrovisha_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha_2":
			dialog.text = "Kesinlikle! Anlıyorsun. Para mutluluk getirmez, ama yokluğu kesinlikle mutsuz eder. Bunu fazlasıyla iyi biliyorum...";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie":
			dialog.text = "İlginç. Pratik. Bende bir arkebüz var... Gerçek bir tane, fatihler zamanından kalma. Bunu bana bir rahip hediye etti. Bazen bulduğum tüm altınlardan daha değerli olduğunu düşünüyorum. Ama... sorunlarımı çözmeyecek.";
			link.l1 = "İyi silahlar birçok sorunu çözebilir. Ve asla sizi yarı yolda bırakmazlar.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie_2":
			dialog.text = "Bunda doğruluk payı var. Ama bazı savaşlar silah gücüyle kazanılamaz.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_znania":
			dialog.text = "Bilgi... Evet, anlıyorum. Fethecilere, hazinelere dair bulabildiğim her şeyi inceledim. Hazine avcılığı üzerine baştan sona bir el kitabı hazırladım. Geminin tüfekli birliği için düzenli talim ve ödül sistemi kurdum. Her kaptan bu el kitabını almak isterdi. Ama bütün bu bilgi... Eğer sonuç getirmiyorsa hiçbir işe yaramıyor. Gerçek sonuçlara.";
			link.l1 = "Ama sonuçlara ulaşmayı sağlayan şey bilgidir. Onsuz, her arayış karanlıkta dolaşmaktan ibarettir.";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "LadyBeth_DialogInCity_Second_4":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Well, it's already late, and I have a lot of work to do";
			else sStr = "Well, I have a lot of work to do";
			dialog.text = ""+sStr+". Konuşma için teşekkür ederim, Kaptan. Gerçekten ilginçti.";
			link.l1 = "Sana da teşekkür ederim. "+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_5":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Third = true;
		break;
		
		case "LadyBeth_DialogInCity_Third_2": // третий диалог
			dialog.text = "Ah, "+pchar.name+"!   Seni gördüğüme sevindim. Harika haberlerim var - sonunda sorunlarıma bir çözüm buldum. Yakında bir sefere çıkacağım ve bu sefer gerçek bir hazineyle döneceğim! Bu arada, dostça bir tavsiye - Cayman'dan uzak dur. Artık orası benim bölgem.";
			link.l1 = "Cayman sana ait değil, Albert. Üzerinde taç hakkın yok. Bu korsanlık.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma";
			link.l2 = "Beni tehdit mi ediyorsun, Blackwood?";
			link.l2.go = "LadyBeth_DialogInCity_Third_3_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma":
			dialog.text = "Taç hakları mı? Bristol'un kenar mahallelerinde yaşamalıydın, "+pchar.name+", o zaman bu belgelerin ne kadar değerli olduğunu anlardın. Aç kaldığında, yasa hiçbir anlam ifade etmez. Yine de... haklısın. Resmi olarak adada hiçbir hakkım yok. Ama yıllardır aradığım şeyi orada buldum. Ve kimsenin onu elimden almasına izin vermem.";
			link.l1 = "Umarım tehlikeli bir yolda olduğunu anlıyorsun.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma_2":
			dialog.text = "Yolumun kolay olmayacağını her zaman biliyordum. Elveda, "+pchar.name+" . Belki tekrar karşılaşırız.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie":
			dialog.text = "Tehdit mi? Hayır, hiç de değil. Sadece bir kaptandan diğerine dostça bir tavsiye. Cayman tehlikelidir... özellikle de işlerime burnunu sokanlar için.";
			link.l1 = "Sözde 'öğüdünü' unutmayacağım. Cayman'da bol şans.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie_2":
			dialog.text = "Ve sana da bol şans, Kaptan. Umarım ihtiyacın olmaz. Elveda.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_4":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Fourth = true;
		break;
		
		// Ловушка, абордаж в каюте
		case "LadyBeth_abordage":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Sen mi?!! Teslim olacağımı mı sandın? Yoksulluğa geri döneceğimi mi düşündün? Açlıktan gebermektense ölmeyi tercih ederim! Ne merhamet, ne ödül, ne zafer! Ranzanın altında bir barut fıçısı var... Hepimiz dibe gideceğiz!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
			else
			{
				dialog.text = "Sen kim oluyorsun da bana saldırıyorsun?! Teslim olacağımı mı sandın? Hayır! O sefil mahallelerde tekrar aç kalmaktansa ölmeyi tercih ederim! Ne merhamet, ne ödül, ne de zafer! Ranzanın altında bir barut fıçısı var... Hepimiz denizin dibini boylayacağız!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
		break;
		
		// Блеквуд разговаривает с ГГ перед битвой на Каймане
		case "LadyBeth_BlackWood_Boss":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Kaptan! Seni uyarmıştım. Şimdi merakının bedelini ödeyeceksin.";
			}
			else
			{
				dialog.text = "Sen kimsin ve nasıl cüret edersin bölgeme girmeye?! Bu ada benim!";
			}
			link.l1 = "Göreceğiz, Blackwood. Bugün bu dünyada bir takıntılı adam daha eksilecek.";
			link.l1.go = "LadyBeth_BlackWood_Boss_oruzhie_1";
			link.l2 = "Bunu barışçıl bir şekilde çözelim, Blackwood. Gidebilirim.";
			link.l2.go = "LadyBeth_BlackWood_Boss_torgovlya_1";
			link.l3 = "Blackwood, sen aklı başında bir adamsın! Bir subaysın! Kampının üzerinde kraliyet bayrağı dalgalanıyor, Tanrı aşkına! Anlaşmaya varamaz mıyız?";
			link.l3.go = "LadyBeth_BlackWood_Boss_harizma_1";
		break;
		
		case "LadyBeth_BlackWood_Boss_oruzhie_1":
			dialog.text = "Takıntılı mı? Ha! Ben sadece ne istediğini bilen bir adamım!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_1":
			dialog.text = "Gitmek mi? Gördüklerinden sonra mı? Hayır, hayır, hayır! Burada ne bulduğumu kimse bilmemeli. Kimse!";
			link.l1 = "Sana söz veriyorum, kimseye söylemeyeceğim. Bir kaptanın onuruna yemin ederim.";
			link.l1.go = "LadyBeth_BlackWood_Boss_torgovlya_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_2":
			dialog.text = "Bu dünyada onur yok, Kaptan. Sadece pislik, yoksulluk ve küçümseme var. Üzgünüm, ama burada ölmelisin.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
		break;
		
		case "LadyBeth_BlackWood_Boss_harizma_1":
			dialog.text = "Çok düşündüm. Uzun uzun düşündüm. Ve fark ettim ki - bu benim tek şansım. Ya Cortez'in altınını bulurum, ya da... hiçbir şey. Anlıyor musun? HİÇBİR ŞEY! Eski hayatıma dönmem! O pisliğe ve yoksulluğa geri dönmem! Burada ölmek daha iyi!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_2":
			dialog.text = "Savaşa! Bullock, Fraser - yaklaşırlarsa saçma ateşi açın! Hopkins, hücum!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_CaimanKino_11");
		break;
		
		// Диалоги с офицерами
		case "LadyBeth_Helena_1": // Элен
			dialog.text = "İyi misin?";
			link.l1 = "Evet, her şey yolunda. Ya sen?";
			link.l1.go = "LadyBeth_Helena_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Helena_2":
			dialog.text = "Hayattayım. Ama bu kara savaşları bana göre değil. Ayağımın altında bir güverte olsun, her gemiyi paramparça ederim, ama burada... tuhaf bir yer. Yüz deniz kurdunu karaya çıkarmak, kazma sallatmak, tahkimat yaptırmak... Benim işim değil.";
			link.l1 = "Blackwood tayfasını nasıl motive edeceğini iyi bilirdi.";
			link.l1.go = "LadyBeth_Helena_3";
		break;
		
		case "LadyBeth_Helena_3":
			dialog.text = "Onun hakkında Bluefield'da duymuştum. Birçok İngiliz denizci ondan saygıyla bahsederdi. Filonun en iyi subayıydı, parlak bir kariyeri vardı... ve birdenbire her şeyi bırakıp hazine peşine düştü.";
			link.l1 = "Onun hakkında ne düşünüyorsun?";
			link.l1.go = "LadyBeth_Helena_4";
		break;
		
		case "LadyBeth_Helena_4":
			dialog.text = "Bence Blackwood'un örneği, bizim... yani senin, adamlarının önünde taşıdığın sorumluluğun ağırlığını açıkça gösteriyor. Lütfen, onun gibi bir kaptana dönüşme.";
			link.l1 = " Deneyeceğim, Helen.";
			link.l1.go = "LadyBeth_Helena_5";
		break;
		
		case "LadyBeth_Helena_5":
			dialog.text = "Teşekkür ederim, Kaptanım. Başaracağına inanıyorum.";
			link.l1 = "Yapacağız.";
			link.l1.go = "LadyBeth_Helena_6";
		break;
		
		case "LadyBeth_Helena_6":
			dialog.text = "Yapacağız.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Helena_7";
		break;
		
		case "LadyBeth_Helena_7":
			DialogExit();
			ReturnOfficer_Helena();
		break;
		
		case "LadyBeth_Mary_1": // Мэри
			dialog.text = "Charles... burada olmak ne kadar korkunç.";
			link.l1 = "İyi misin, Mary? Gerçek bir asker gibi dayandın.";
			link.l1.go = "LadyBeth_Mary_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Mary_2":
			dialog.text = "Hayır, iyi değilim, tamam mı. Şu insanlara bak! Yorgunluktan bitap düştüler, açlık içinde yaşadılar, hastalıklardan öldüler... Peki, ne için? Belki de hiç var olmayan bir altın için.";
			link.l1 = "Blackwood buranın olduğuna inanıyordu.";
			link.l1.go = "LadyBeth_Mary_3";
		break;
		
		case "LadyBeth_Mary_3":
			dialog.text = "Bu kırmızı ceket... tam olarak benimkisi gibi. Bir İngiliz subayı... Biliyor musun, birden aklıma ailem geldi, tamam mı. Köklerimi düşündüm... hiç bilmediğim şeyleri. Belki ben de onlardan biriyim?";
			link.l1 = "Bunlardan biri mi?";
			link.l1.go = "LadyBeth_Mary_4";
		break;
		
		case "LadyBeth_Mary_4":
			dialog.text = "Belki de hiç var olmayan bir şeyi arayanlar. Sonra da bu arayışta kendini kaybedenler. Ben... Bunu sonra konuşmak isterim, olur mu? Şu korkunç yerden çıkınca.";
			link.l1 = "Elbette, Mary.";
			link.l1.go = "LadyBeth_Mary_5";
		break;
		
		case "LadyBeth_Mary_5":
			dialog.text = "Önce onu gömelim, olur mu? Hak etmese bile. Bir zamanlar olduğu adamın hatırı için.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Mary_6";
		break;
		
		case "LadyBeth_Mary_6":
			DialogExit();
			ReturnOfficer_Mary();
		break;
		
		case "LadyBeth_Tichingitu_1": // Тичингиту
			dialog.text = "Kaptan, Tichingitu burayı kötü bir yer olarak görüyor. Çok kötü bir yer.";
			link.l1 = "Ne demek istiyorsun?";
			link.l1.go = "LadyBeth_Tichingitu_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Tichingitu_2":
			dialog.text = "Bu ada artık lanetli. Toprak çok fazla kan ve gözyaşı emdi. Burada kim kazarsa, bu laneti solur.";
			link.l1 = "Blackwood'un içine şeytan mı girmişti, diyorsun?";
			link.l1.go = "LadyBeth_Tichingitu_3";
		break;
		
		case "LadyBeth_Tichingitu_3":
			dialog.text = "Sadece ele geçirilmiş değil. O... nasıl desem... boş bir kap gibi. İçine bir şey girip ruhunu dışarı atmış. Bunu daha önce de gördüm. Kabilemin şamanı ruhlara insan kurban ettiğinde. O şamanın da yüzü aynıydı.";
			link.l1 = "Ama böyle bir takıntıya ne sebep olabilir?";
			link.l1.go = "LadyBeth_Tichingitu_4";
		break;
		
		case "LadyBeth_Tichingitu_4":
			dialog.text = "İçi boş bir adamın zihni başkalarının düşünceleriyle kolayca doldurulur. Birisi onun zayıf noktasını bulur ve kullanır. Tichingitu bu adam için neredeyse üzülüyor.";
			link.l1 = "Neredeyse mi?";
			link.l1.go = "LadyBeth_Tichingitu_5";
		break;
		
		case "LadyBeth_Tichingitu_5":
			dialog.text = "Evet, neredeyse. Her savaşçı kendi seçiminin sorumluluğunu taşır. Şeytanlar kulağına fısıldasa bile.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Tichingitu_6";
		break;
		
		case "LadyBeth_Tichingitu_6":
			DialogExit();
			ReturnOfficer_Tichingitu();
		break;
		
		case "LadyBeth_Irons_1": // Томми
			dialog.text = "Kahretsin, Kaptan! Şuna bir bak! Tıpkı eski güzel günlerdeki gibi!";
			link.l1 = "Karada savaşın nasıl bir şey olduğunu iyi bilirsin.";
			link.l1.go = "LadyBeth_Irons_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Irons_2":
			dialog.text = "Bana Naseby Muharebesi'ni hatırlatıyor. Bizim süvari kanadımız, Rupert'ın süvarileriyle çarpışmıştı. Kralı için aynı vahşilikle savaştılar.";
			link.l1 = "Blackwood hakkında ne düşünüyorsun?";
			link.l1.go = "LadyBeth_Irons_3";
		break;
		
		case "LadyBeth_Irons_3":
			dialog.text = "Bu Blackwood ya bir dahi ya da tam bir kaçıktı. Bence ikisi birden. Beni asıl şaşırtan ne biliyor musun? Adamları. Birçoğu eski asker. Sokak serserileri değil, gerçekten asker. Ve hepsi bu deliliğinde onu takip etti. Hatta Fox'un deniz piyadeleri bile. Ha! Bugünkü kıyımdan en çok kim memnun olacak dersen, işte o! Onların firarını asla affetmedi.";
			link.l1 = "Belki de mesele paradır?";
			link.l1.go = "LadyBeth_Irons_4";
		break;
		
		case "LadyBeth_Irons_4":
			dialog.text = "Yok, başka bir şey var. Bu adam onların üzerinde bir güce sahipti. Gerçek bir güç. Ayrıca Barbadoslu zengin bir kızla nişanlı olduğunu da duydum. Bunca hazineyi aldıktan sonra onunla evlenmemesi tuhaf. Tipik bir asker - savaşın ne zaman biteceğini bilmiyordu.";
			link.l1 = "Teşekkürler, Tommy. Gerçekten akıllı birisin.";
			link.l1.go = "LadyBeth_Irons_5";
		break;
		
		case "LadyBeth_Irons_5":
			dialog.text = "Ha?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "LadyBeth_Irons_6";
		break;
		
		case "LadyBeth_Irons_6":
			DialogExit();
			ReturnOfficer_Irons();
		break;
		
		case "LadyBeth_Knippel_1": // Книппель
			dialog.text = "Bunu görmek ne acı, Kaptan. Ne hallere düştük?!";
			link.l1 = "Biz mi?";
			link.l1.go = "LadyBeth_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Knippel_2":
			dialog.text = "İngiliz filosu! Şuna bak: şu ölü pisliklerin arasında yatan kırmızı ceketli küçük noktalar!";
			link.l1 = "Bu 'pisliklerin' bazıları bizim insanımız, Charlie. Duygularını anlıyorum, ama...";
			link.l1.go = "LadyBeth_Knippel_3";
		break;
		
		case "LadyBeth_Knippel_3":
			dialog.text = "Siktir et, efendim!";
			link.l1 = "Duygularını anlıyorum, ama öfkeni ve hayal kırıklığını Blackwood'a yöneltsen daha iyi olur. Senin çok sevdiğin İngiliz filosundan kaçan ve onları buraya getiren oydu.";
			link.l1.go = "LadyBeth_Knippel_4";
			link.l2 = "Gerçekten de. Hadi gidelim, gün henüz bitmedi.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_4":
			dialog.text = "Sadece komutanlarının emirlerini yerine getiriyorlardı!";
			link.l1 = "Fleetwood'u takip ettiğin gibi mi?";
			link.l1.go = "LadyBeth_Knippel_5";
			link.l2 = "Elbette. Hadi gidelim, gün daha bitmedi.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_5":
			dialog.text = "Sanki seni takip ediyorum!";
			link.l1 = "Umarım Blackwood ve Fleetwood'dan daha iyi bir kaptan olduğumu kanıtlayabilirim. Hadi gidelim, gün henüz bitmedi.";
			link.l1.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_6":
			dialog.text = "Elbette, Kaptan. Ve bittiğinde – bir sonrakine kadar içmeye devam edeceğim.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Knippel_7";
		break;
		
		case "LadyBeth_Knippel_7":
			DialogExit();
			ReturnOfficer_Knippel();
		break;
		
		case "LadyBeth_Alonso_1": // Алонсо
			dialog.text = "Madre de Dios, Kaptan! İyi misiniz?";
			link.l1 = "Bunu henüz bilmiyoruz. Kaç adam kaybettik?";
			link.l1.go = "LadyBeth_Alonso_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Alonso_2":
			
			dialog.text = "Öldürüldü mü? Bu macerada kaybettiğimiz "+sti(pchar.SailorDiedInBattleInfo)+" adamlar. Müdahaleci görünmek istemem, Kaptan, ama... sizi uyarmıştım!";
			link.l1 = "Bu lafını görmezden geleceğim çünkü bugün kendini kanıtladın, Alonso. Bu kadar yeteneği nereden buldun?";
			link.l1.go = "LadyBeth_Alonso_3";
		break;
		
		case "LadyBeth_Alonso_3":
			dialog.text = "Bir gün sana o hikayeyi anlatırım, Kaptan - tabii yeterince uzun yaşarsak.";
			link.l1 = "Başka değerli bir tavsiyen var mı?";
			link.l1.go = "LadyBeth_Alonso_4";
		break;
		
		case "LadyBeth_Alonso_4":
			dialog.text = "Eğer burada hazineler olsaydı, çoktan bulurlardı. Ama yine de adayı aramalı ve hayatta kalanları bulup, onlara ne yapacağımıza karar vermeliyiz. Bir de Blackwood'un gemisini unutmamalıyız: o güzel kar gemisi hakkında hep iyi şeyler duydum. Böyle bir ödülü kaçırmak yazık olurdu, Kaptan. Tabii ki, ben sadece mürettebatın bu konudaki düşüncesini iletiyorum.";
			link.l1 = "Elbette. Hadi gidelim. Ganimetler bizi bekliyor!";
			link.l1.go = "LadyBeth_Alonso_5";
		break;
		
		case "LadyBeth_Alonso_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		// Диалог с матросом в гроте Каймана
		case "LadyBeth_MatrosyInGrot":
			dialog.text = "Ateş etmeyin! Teslim oluyoruz!";
			link.l1 = "Sen kimsin?";
			link.l1.go = "LadyBeth_MatrosyInGrot_2";
		break;
		
		case "LadyBeth_MatrosyInGrot_2":
			dialog.text = "Biz... biz 'Lady Beth'teniz. Kaptan Blackwood'un tayfasıyız. O... o hayatta mı?";
			link.l1 = "Hayır. Kaptanınız öldü.";
			link.l1.go = "LadyBeth_MatrosyInGrot_3";
		break;
		
		case "LadyBeth_MatrosyInGrot_3":
			dialog.text = "Her şey bitti demek... Tanrı'ya şükür.";
			link.l1 = "Kaptanınızın yasını tutuyor gibi görünmüyorsunuz.";
			link.l1.go = "LadyBeth_MatrosyInGrot_4";
		break;
		
		case "LadyBeth_MatrosyInGrot_4":
			dialog.text = "Anlamıyorsun. Blackwood büyük bir adamdı. Tanıdığım en iyi kaptandı. Ama son aylarda... değişti. Takıntılı, zalim biri oldu. Bizi gece gündüz çalıştırdı, belki de hiç var olmayan bir şeyi arıyorduk.";
			link.l1 = "Seni tayfama alıyorum. Deneyimli denizcilere ihtiyacımız var.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda";
			link.l2 = "Yenilenin vay haline, çocuklar. Artık yeriniz benim ambarımda. Şanslıysanız, Barbados'taki bir plantasyonu görmeye yaşarsınız.";
			link.l2.go = "LadyBeth_MatrosyInGrot_PlusRaby";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda":
			dialog.text = "Gerçekten mi? Sen... sen korkmuyor musun bizim... bunca şeyden sonra bizde bir tuhaflık olduğundan?";
			link.l1 = "Herkes ikinci bir şansı hak eder.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda_1";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda_1":
			dialog.text = "Teşekkür ederim, Kaptan. Yemin ederim, pişman olmayacaksınız. Biz iyi denizciyiz. Ve... belki artık kâbuslar da sona erer.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 30;
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusRaby":
			dialog.text = "Teşekkürler, teşekkürler! En azından hayatta kalacağız. Lütfen bizi buradan çıkarın. Bu ada... sanki lanetlenmiş gibi.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+30);
		break;
		
		case "LadyBeth_MatrosyInGrot_exit":
			DialogExit();
			for (i=1; i<=8; i++)
			{
				sld = CharacterFromID("LadyBeth_MatrosyPryachutsya_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		// Диалог с матросом на Леди Бет
		case "LadyBeth_EnemyMatros_1":
			dialog.text = "Ne oluyor lan?! 'Lady'ye saldırmaya ve Jeremy'yi öldürmeye nasıl cüret edersiniz? Buradan sağ çıkamayacaksınız, alçaklar, kaptan geri dönecek ve...";
			link.l1 = "Kaptanınız öldü. İlk ateşi Jeremy açtı ve ben de kanla ödenmiş yasal ganimet olarak 'Leydi'nizi alıyorum.";
			link.l1.go = "LadyBeth_EnemyMatros_2";
		break;
		
		case "LadyBeth_EnemyMatros_2":
			dialog.text = "Kaptan... öldü mü? Yalan söylüyorsun, köpek! Onun üniformasındaki bir düğmeye bile değmezsin!";
			link.l1 = "Eğer o üniformanın bir anlamı vardıysa, o da çoktan gitmiş olan Blackwood içindi. Seçim sizin – ölü bir adam için savaşmak mı, yoksa hayatınızı kurtarmak mı?";
			link.l1.go = "LadyBeth_EnemyMatros_3";
		break;
		
		case "LadyBeth_EnemyMatros_3":
			if (CharacterIsHere("Helena"))
			{
				StartInstantDialog("Helena", "LadyBeth_EnemyMatros_Helena_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Knippel"))
			{
				StartInstantDialog("Knippel", "LadyBeth_EnemyMatros_Knippel_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Irons"))
			{
				StartInstantDialog("Irons", "LadyBeth_EnemyMatros_Irons_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			dialog.text = "Sana gemiyi savaşmadan vermeyeceğiz!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		case "LadyBeth_EnemyMatros_Helena_1":
			dialog.text = "Dinleyin, arkadaşlar. Kaptanınıza sadık olduğunuzu biliyorum. Bu, saygıdeğer bir şey. Ama o artık öldü, siz ise hayattasınız. Ve bundan sonra nasıl yaşayacağınıza siz karar vereceksiniz. Size yeniden başlama fırsatı sunuyoruz.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_Knippel_1":
			dialog.text = "Kaptan, bu adamlar düşman değil. Sadece emirleri yerine getiriyorlardı. Birçoğu eski kraliyet denizcisi, iyi eğitimli ve disiplinli. Yeteneklerinden faydalanmamak israf olurdu. Delikanlılar, uzun yıllar filoda görev yaparken ben de sizin yerinizde oldum, hem de bir kereden fazla. Ve doğru kararı verdim. Siz de verin.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
		break;
		
		case "LadyBeth_EnemyMatros_Irons_1":
			dialog.text = "Peki, denizciler! Seçim basit - ya hayatta kalırsınız, ya ambarımızda tutsak olarak ya da tayfamıza katılıp iyi erzak ve düzenli maaş alarak, ya da... (parmağını boğazında gezdirir) Ben olsam ilkini seçerdim!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_10";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_5":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_6", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_6":
			dialog.text = "...";
			link.l1 = "Artık mürettebatımın bir parçası olacaksın.";
			link.l1.go = "LadyBeth_EnemyMatros_7";
			link.l2 = "Yenilenlere yazıklar olsun, çocuklar. Şimdi yeriniz benim ambarımda. Şanslıysanız, Barbados'taki bir plantasyonu görecek kadar yaşarsınız.";
			link.l2.go = "LadyBeth_EnemyMatros_9";
		break;
		
		case "LadyBeth_EnemyMatros_7":
			dialog.text = "Bunca şeyden sonra bizi tayfana mı alıyorsun?";
			link.l1 = "İyi denizciler her zaman değerlidir. Ve Kaptan Blackwood adamlarını seçmeyi iyi bilirdi.";
			link.l1.go = "LadyBeth_EnemyMatros_8";
		break;
		
		case "LadyBeth_EnemyMatros_8":
			dialog.text = "Teşekkürler, Kaptan. Sizi hayal kırıklığına uğratmayacağız.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 12;
		break;
		
		case "LadyBeth_EnemyMatros_9":
			dialog.text = "Pekâlâ... en azından bu macera başka türlü sona eremezdi. Bizi affedin, Kaptan Blackwood. Sizi koruyamadık.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+12);
		break;
		
		case "LadyBeth_EnemyMatros_10":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_11", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_11":
			dialog.text = "Sana gemiyi savaşmadan vermeyiz!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		// Диалог с Элизабет Бишоп
		case "LadyBeth_Elizabeth_1":
			dialog.text = "...";
			link.l1 = "Affedersiniz. Siz Elizabeth misiniz?";
			if (pchar.sex == "man") link.l1.go = "LadyBeth_Elizabeth_2";
			if (pchar.sex == "woman") link.l1.go = "LadyBeth_Elizabeth_Woman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Elizabeth_2":
			dialog.text = "Evet, o benim. Peki, sen kimsin?";
			link.l1 = "Kaptan "+GetFullName(pchar)+". Ben... Albert Blackwood'u tanıyordum.";
			link.l1.go = "LadyBeth_Elizabeth_3";
		break;
		
		case "LadyBeth_Elizabeth_3":
			dialog.text = "Benim Albert’im mi? Aman Tanrım... O... o iyi mi?";
			link.l1 = "Maalesef, hayır. Savaşta öldü. Sonuna kadar savaştı.";
			link.l1.go = "LadyBeth_Elizabeth_4";
		break;
		
		case "LadyBeth_Elizabeth_4":
			dialog.text = "Ben... Ben de öyle düşünmüştüm. Onca yıl tek bir haber bile gelmedi... Biliyor musun, onu bekledim. Çok uzun süre bekledim. Babam, Albert’in sadece terfi almasını beklemesi gerektiğini söyledi. Vali zaten her şeyi kararlaştırmıştı, birkaç ay meselesiydi. Ama Albert... o konuşmayı bambaşka anladı. Zengin döneceğini, elime layık olacağını söyledi. Ve gitti. Sadece... gitti.";
			link.l1 = "Son gününe kadar seni düşündü.";
			link.l1.go = "LadyBeth_Elizabeth_5";
		break;
		
		case "LadyBeth_Elizabeth_5":
			dialog.text = "Ne kadar aptalca. Onun hazinelerine ihtiyacım yoktu. Ben onu seviyordum, parasını değil. Onunla kaçmaya hazırdım... ama o çok gururluydu. Bir mektup, bir haber bekledim... Sonra sadece bu garip el kitabı geldi. Ne kadar soğuk, ne kadar hesapçı bir belgeydi... Hiç tanıdığım Albert gibi değildi. O zaman onu kaybettiğimi anladım.";
			link.l1 = "Eşyalarının arasında bunu buldum.";
			link.l1.go = "LadyBeth_Elizabeth_6";
		break;
		
		case "LadyBeth_Elizabeth_6":
			dialog.text = "Evimin haritası mı? Ben onun en değerli hazinesi miydim? Ne ironik. Karayipler’in dört bir yanında servet aradı, ama onun için gerçekten önemli olan tek şey hep buradaydı... Dur. Sana verecek bir şeyim var. Bu, Albert’in el kitabı. Bir yıl önce bana göndermişti. Hazine bulmasına ve bana geri dönmesine yardımcı olacağını söylemişti. Artık bu kitap sana daha çok yarar sağlar.";
			link.l1 = "Teşekkür ederim, Elizabeth. Her şeyin böyle sonuçlanmasına üzgünüm.";
			link.l1.go = "LadyBeth_Elizabeth_7";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_7":
			dialog.text = "Ve ben evlendim, Kaptan. Bay Bishop'la. Babam ısrar etti. Bu adamı tanımıyorsun... ve tanımak da istemezdin. Her gün düşünüyorum, eğer Albert sadece... geri dönseydi hayatım nasıl olurdu diye.";
			link.l1 = "Bunu da şimdi düşüneceğim.";
			link.l1.go = "LadyBeth_Elizabeth_8";
		break;
		
		case "LadyBeth_Elizabeth_8":
			dialog.text = "Hoşça kal, Kaptan. Ve... kendine dikkat et. Hayaletlerin peşinden koşma.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		case "LadyBeth_Elizabeth_Woman_2":
			dialog.text = "Evet, o benim.";
			link.l1 = " Kaptan Helen MacArthur. Ben... Albert Blackwood'u tanıyordum.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_3";
		break;
		
		case "LadyBeth_Elizabeth_Woman_3":
			dialog.text = "Benim Albert’im mi? Aman Tanrım... O... Peki sen kimsin?";
			link.l1 = "Kaptan Helen MacArthur, dedim sadece. Kendi gemimi yönetiyorum.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_4";
		break;
		
		case "LadyBeth_Elizabeth_Woman_4":
			dialog.text = "Kaptan mı? Kadın kaptan mı? Sen... Sen Albert’le miydin? Hangi anlamda... onu tanıyordun?";
			link.l1 = "Sadece bir kaptan olarak. Üzgünüm, ama Albert öldü. Son savaşına bizzat tanık oldum.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_5";
		break;
		
		case "LadyBeth_Elizabeth_Woman_5":
			dialog.text = "Anlıyorum. Şüphelerim için affet beni. Sadece... Kaptan Blackwood her zaman kadınların ilgisini çekerdi. Burada, Barbados'ta bile. Hatta özellikle burada.";
			link.l1 = "Onu sevdin.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_6";
		break;
		
		case "LadyBeth_Elizabeth_Woman_6":
			dialog.text = "Tüm kalbimle. Babam, Albert'in sadece terfi almasını beklemesi gerektiğini söyledi. Birkaç ay meselesiydi. Ama o, babamın sözlerini yoksulluktan dolayı bir reddediş olarak anladı. Hazineyle döneceğini söyledi. Ve gitti.";
			link.l1 = "Erkekler ve onların gururu!";
			link.l1.go = "LadyBeth_Elizabeth_Woman_7";
		break;
		
		case "LadyBeth_Elizabeth_Woman_7":
			dialog.text = "Şanslısın, Kaptan MacArthur. Özgürsün. İstediğin yere yelken açabiliyorsun. Ne plantasyon sahipleri, ne de kaderini belirleyen babalar var. Seni malı gibi gören kocalar da yok.";
			link.l1 = "Özgürlüğün bedeli ağırdır. Ve onu her gün savunmak zorundasın.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_8";
		break;
		
		case "LadyBeth_Elizabeth_Woman_8":
			dialog.text = "Bu konuda sana yardımcı olabilecek bir şeyim olabilir. Al, bunu al. Bu onun define avcılığı el kitabı. Albert bunu bana yaklaşık bir yıl önce gönderdi. Hayatında yarattığı en iyi şey olduğunu söyledi. Zenginleşmesine ve bana dönmesine yardımcı olacağını düşünüyordu. Ama her sayfayla birlikte, tanıdığım Albert'ten giderek daha çok uzaklaştı.";
			link.l1 = "Teşekkür ederim. Bunu saklayacağım.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_9";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_Woman_9":
			dialog.text = "Lütfen, Kaptan... özgürlüğünüzün kıymetini bilin. Albay Bishop'la evlendim. Babamın bile korktuğu bir adam. Eğer ben de sizin gibi özgür olsaydım... Her şey bambaşka olurdu.";
			link.l1 = "Biliyorum.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_10";
		break;
		
		case "LadyBeth_Elizabeth_Woman_10":
			dialog.text = "Elveda, Kaptan. Sana da rüzgarlar dost olsun.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
	}
} 