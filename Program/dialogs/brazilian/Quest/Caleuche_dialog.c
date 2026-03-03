void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Isso com certeza é um erro. Você pode avisar o Jason sobre quando e como isso aconteceu.";
			link.l1 = "Pode deixar.";
			link.l1.go = "exit";
		break;
		
		// шаман карибов Туттуатхапак
		case "Tuttuat":
			dialog.text = "Por que você veio à minha cabana, homem branco? Tuttuathapak não considera você um convidado querido.";
			if (GetCharacterFreeItem(pchar, "mushket1") || GetCharacterFreeItem(pchar, "mushket2") || GetCharacterFreeItem(pchar, "mushket7"))
			{
				link.l1 = "Saudações a você, grande xamã Tuttuathapak. Vim buscar sua ajuda e conselho. Por favor, aceite este mosquete como prova da minha boa vontade.";
				link.l1.go = "Tuttuat_1";
			}
			else
			{
				link.l1 = "Saudações a você, grande xamã Tuttuathapak. Vim buscar sua ajuda e conselho.";
				link.l1.go = "Tuttuat_exit";
			}
		break;
		
		case "Tuttuat_exit":
			dialog.text = "Tuttuathapak não vai ajudar homem branco. Homens brancos são maus. Eles matam e conquistam índios, fazem índios de escravos. Tuttuathapak não dá conselho para homem branco. Agora você vai embora.";
			link.l1 = "Hmm...";
			link.l1.go = "Tuttuat_exit_1";
		break;
		
		case "Tuttuat_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat";
		break;
		
		case "Tuttuat_1":
			if (GetCharacterFreeItem(pchar, "mushket1")) 
			{
				sTemp = "mushket1";
			}
			else 
			{
				if(GetCharacterFreeItem(pchar, "mushket2"))
				{
					sTemp = "mushket2";
				}
				else
				{
					sTemp = "mushket7";
				}
			}
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have given: "+XI_ConvertString(sTemp)+"");
			dialog.text = "Você sabe o que oferecer a Tuttuathapak, homem branco. Tuttuathapak aceita seu presente. Ele vai falar. Que conselho você busca de mim?";
			link.l1 = "Ouvi dizer que você veio de um lugar distante no sul. Tenho um amuleto indígena, e um homem entendido me disse que talvez você saiba como ele pode ser usado.";
			link.l1.go = "Tuttuat_2";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_2":
			dialog.text = "Mostrar o amuleto.";
			link.l1 = "Aqui está, grande xamã.";
			link.l1.go = "Tuttuat_3";
		break;
		
		case "Tuttuat_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(olhando para o amuleto)... Seu amigo fala a verdade, homem branco. Este amuleto pertenceu ao meu povo, os grandes índios, Chavin era o nome deles. Um maldito, blasfemo, cão de rosto pálido profanou o santuário e o trouxe para cá. Tuttuathapak puniu esse desgraçado.";
			link.l1 = "Você tirou a sanidade dele, pelo visto?";
			link.l1.go = "Tuttuat_4";
		break;
		
		case "Tuttuat_4":
			dialog.text = "O homem branco surpreende Tuttuathapak com seu conhecimento. Sim, eu devorei a mente daquele desgraçado sarnento. Ele e seus homens imundos tiveram o que mereciam.";
			link.l1 = "Entendo... Diga-me, xamã, para que serve este amuleto? Talvez ele possa proteger alguém em batalha ou afastar magia maligna?";
			link.l1.go = "Tuttuat_5";
		break;
		
		case "Tuttuat_5":
			dialog.text = "Esse amuleto não serve para você, capitão branco. Você não pode usar o poder dele. Só os grandes xamãs da nossa tribo sabem como despertá-lo.";
			link.l1 = "Hmm... Então, pelo visto fiz toda essa longa viagem à toa. Mas talvez você consiga despertar o poder deste amuleto, grande xamã? Com certeza podemos chegar a um acordo...";
			link.l1.go = "Tuttuat_6";
		break;
		
		case "Tuttuat_6":
			dialog.text = "Mesmo que eu desperte o amuleto, você não conseguirá manter o poder dele por muito tempo. Mas eu lhe ofereço um acordo, homem branco.";
			link.l1 = "Que tipo de acordo?";
			link.l1.go = "Tuttuat_7";
		break;
		
		case "Tuttuat_7":
			dialog.text = "Três amuletos como este foram levados do nosso santuário. Eles têm poderes diferentes, mas se forem reunidos, se tornam muito, muito poderosos. Encontre os três amuletos e traga-os para mim, e eu vou te recompensar. Vou te dar um poder que você poderá guardar para sempre.";
			link.l1 = "Eu não entendo muito bem... Que tipo de poder você está falando?";
			link.l1.go = "Tuttuat_8";
		break;
		
		case "Tuttuat_8":
			dialog.text = "Você saberá tudo no momento certo. Encontre e traga para mim os três amuletos. Eles estão no Caribe. Procure por eles e os encontre. Você vai reconhecê-los facilmente – eles são parecidos. Vá, homem branco. Tuttuathapak espera e pede aos espíritos que te ajudem.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_9";
		break;
		
		case "Tuttuat_9":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "ghostship"; 
			AddQuestRecord("Caleuche", "3");
			pchar.quest.Caleuche_ghostship.win_condition.l1 = "location";
			pchar.quest.Caleuche_ghostship.win_condition.l1.location = "Dominica";
			pchar.quest.Caleuche_ghostship.function = "Caleuche_PrepareGhostship";
		break;
		
		case "Tuttuat_10":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Vá, homem branco. Encontre mais dois amuletos.";
				link.l1 = "Já os encontrei, grande xamã. Aqui, dê uma olhada.";
				link.l1.go = "Tuttuat_33";
			}
			else
			{
				dialog.text = "Vá, homem branco. Encontre os outros dois amuletos.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_10_1";
			}
		break;
		
		case "Tuttuat_10_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
		break;
		
		case "Tuttuat_11":
			dialog.text = "Você aqui de novo, branco? Parece que encontrou uma onça brava na selva.";
			link.l1 = "Pior ainda, grande xamã. Assim que entrei no mar, uma tempestade enorme surgiu do nada e fui atacado por um navio tripulado por mortos-vivos! O capitão deles era absolutamente invencível. Primeiro ele tomou o amuleto de mim e quase me matou – sobrevivi por um triz. Depois, quase afundaram meu navio, só alguns poucos da minha tripulação escaparam.";
			link.l1.go = "Tuttuat_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_12":
			dialog.text = "Más notícias, homem branco. O Caleuche vai atacar de novo.";
			link.l1 = "O Caleuche? Aquele capitão morto-vivo chamava o navio dele de Coração Voador. Então, você sabia do navio fantasma e não me avisou? Se eu soubesse que esse pesadelo dos mares estava atrás do amuleto, eu jamais...";
			link.l1.go = "Tuttuat_13";
		break;
		
		case "Tuttuat_13":
			dialog.text = "Tuttuathapak vê que o capitão branco está incomodado. O capitão branco precisa se acalmar.";
			link.l1 = "Calma?! Você ficou louco? Como é que eu vou sobreviver a uma coisa dessas!";
			link.l1.go = "Tuttuat_14";
		break;
		
		case "Tuttuat_14":
			dialog.text = "Sim. Fique calmo e não grite. Me diga – você ainda quer receber de mim um grande poder, que ficará com você para sempre?";
			link.l1 = "Bem, é claro que tenho. Mas não estou mais com o amuleto.";
			link.l1.go = "Tuttuat_15";
		break;
		
		case "Tuttuat_15":
			dialog.text = "Vou te ensinar como pegar o amuleto do capitão do Caleuche. Não vai ser fácil. Mas se conseguir, você vai tomar o navio dele como prêmio, encontrar tesouros valiosos, ganhar glória entre os seus e ainda receber uma recompensa minha.";
			link.l1 = "Maldição! Eu acabaria com aquele monstro mirrado sem pensar duas vezes! Mas como vou derrotá-lo, se ele não pode ser ferido nem por espada, nem por bala?!";
			link.l1.go = "Tuttuat_16";
		break;
		
		case "Tuttuat_16":
			dialog.text = "Está pronto pra me ouvir, capitão branco?";
			link.l1 = "Sim, eu sou, grande xamã.";
			link.l1.go = "Tuttuat_17";
		break;
		
		case "Tuttuat_17":
			dialog.text = "Quando meu pai era um jovem guerreiro, homens brancos vieram à minha terra em um navio chamado Coração Voador. Eles foram para as montanhas. A lenda diz que lá está escondido um santuário dos nossos ancestrais. O santuário dos guerreiros jaguar. Os homens brancos encontraram o santuário e o ouro, e profanaram algo sagrado e antigo. Eles levaram o grande tesouro dos Chavins – o crânio de jade de Yum Cimil, deus da morte e patrono dos homens jaguar. Os homens brancos voltaram ao navio. Decidiram retornar para buscar mais ouro, mas quando um deles pisou em terra firme, morreu em uma dor terrível. Yum Cimil amaldiçoou o capitão e sua tripulação. Eles se tornaram imortais, mas nunca mais poderiam pisar em terra. Navegaram por muitos, muitos invernos, meio século pelo seu calendário. Foi assim que surgiu o Caleuche. Seus corpos secaram, sua carne apodreceu, mas continuaram vivos. Se você cortar um braço ou uma perna, cresce de novo. Se cortá-los ao meio, eles se regeneram. Se o navio afundar, eles o consertam debaixo d’água, e ele volta a navegar.";
			link.l1 = "Que maravilha...";
			link.l1.go = "Tuttuat_18";
		break;
		
		case "Tuttuat_18":
			dialog.text = " O Caleuche aterroriza os marinheiros. Ataca sem motivo e traz desgraça certa. Não aparece com frequência no Caribe. Prefere navegar pelas costas da minha terra natal. Acho que ele quer se livrar da maldição. Mas nunca vai conseguir.";
			link.l1 = "Por quê? O que precisa ser feito para quebrar a maldição?";
			link.l1.go = "Tuttuat_19";
		break;
		
		case "Tuttuat_19":
			dialog.text = "Caveira de jade. Ela precisa ser devolvida ao santuário de Yum Cimil, templo dos guerreiros jaguar. Existem vários templos. Os anciãos da minha tribo dizem que há um em uma pequena ilha no Caribe. Por isso o Caleuche navegou até lá. Assim que a caveira estiver no templo, o feitiço de Yum Cimil se desfaz, eles se tornam mortais e não podem mais curar seus ferimentos.";
			link.l1 = "Ha! Mais provável que eles não vão devolver o crânio! Por que fariam isso, se são imortais e invencíveis? E além disso, simplesmente não podem trazer de volta se não podem pisar em terra firme, não é?";
			link.l1.go = "Tuttuat_20";
		break;
		
		case "Tuttuat_20":
			dialog.text = "Eles não têm o crânio. O capitão o jogou fora nas terras dos meus ancestrais, quando voltou do santuário dos homens-jaguar. Jade não é ouro, o homem branco não precisava disso, ele não conseguiu tirar a bela pedra verde dos olhos do crânio. Então ele o descartou. Um marinheiro o pegou, e ele não foi tocado pela maldição\nQuando o marinheiro viu no que a tripulação do Caleuche havia se transformado, ele fugiu. Veio para nossa aldeia. Meu pai viu aquele marinheiro e o crânio de Yum Cimil. E então o homem branco foi para o norte pela costa e levou o crânio com ele.";
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul"))
				{
					link.l1 = "Um crânio de jade com pedras verdes nas órbitas? Eu cheguei a segurá-lo, acredita? Eu mesmo entreguei para o Solomon. Mas ele foi para a Europa com a filha, e parece que levou o crânio junto.";
				}
				else
				{
					link.l1 = "Um crânio de jade com gemas verdes nas órbitas? Caramba... Eu... Eu segurei ele nas minhas próprias mãos! E vendi pra um português... Merriman, ou algo assim... Isso, foi assim que ele chamou - o crânio de Yum Cimil! Ele queria aquilo de qualquer jeito! Pagou meio milhão de pesos por ele!";
				}
				link.l1.go = "Tuttuat_21_1";
			}
			else
			{
				link.l1 = "Um crânio de jade com gemas verdes nas órbitas? Então é isso que eu preciso encontrar? Mas aquele marinheiro pode ter morrido na selva há cinquenta anos, e o crânio pode estar perdido para sempre!";
				link.l1.go = "Tuttuat_21_2";
			}
		break;
		
		case "Tuttuat_21_1":
			dialog.text = "Eu sei que o crânio está no Caribe. O Caleuche não está aqui por acaso. Nas últimas seis luas, ele tem sido visto com frequência na ilha. Antes disso, fazia muitos invernos que não aparecia por lá. O capitão do Caleuche consegue sentir o artefato dos homens-jaguar. Foi assim que ele encontrou você e seu navio.";
			link.l1 = "Então, entendi direito que eu tenho que encontrar esse crânio de novo? E depois, o que é que eu faço com ele?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_21_2":
			dialog.text = "O crânio deve estar aqui, no Caribe. O Caleuche não está aqui por acaso. Nas últimas seis luas, ele tem sido visto com frequência na ilha. Antes disso, ele ficou muitos invernos sem aparecer. O capitão do Caleuche consegue sentir o artefato dos homens-jaguar. Foi assim que ele encontrou você e seu navio.";
			link.l1 = "Então, entendi direito que eu preciso encontrar esse crânio de novo? E depois, o que é que eu faço com ele?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_22":
			dialog.text = "Primeiro, você precisa encontrar os dois amuletos de que falamos. Sem eles, você não pode fazer nada. Os amuletos lhe dão o poder de enfrentar os homens-jaguar e qualquer inimigo que cruzar seu caminho.";
			link.l1 = "Enfrentar homens-jaguar? Do que você está falando?";
			link.l1.go = "Tuttuat_23";
		break;
		
		case "Tuttuat_23":
			dialog.text = "O templo onde você deve levar o crânio de jade fica numa ilha deserta no Caribe. Ele é guardado por homens-jaguar. Todos estavam mortos, mas agora vivem novamente. Sem o amuleto, você não passará por eles. Em vida, os homens-jaguar eram guerreiros ferozes, e na morte se tornaram quase invencíveis. É o próprio Yum Cimil quem lhes dá força.";
			link.l1 = "Mortos-vivos? De novo? Que sorte a minha...";
			link.l1.go = "Tuttuat_24";
		break;
		
		case "Tuttuat_24":
			dialog.text = "Por que tanta surpresa, capitão branco? Yum Cimil é o deus da morte, o crânio de jade dá poder sobre os mortos e os vivos. Caribe. Ele é guardado por homens-jaguar. Sem o amuleto você não pode passar por eles. Com o amuleto você pode entrar no templo e sobreviver, deixar o crânio lá, depois encontrar o Caleuche, derrotar o capitão dela e recuperar o amuleto que ele tirou de você.";
			link.l1 = "E por que o capitão do Caleuche precisa desses amuletos?";
			link.l1.go = "Tuttuat_25";
		break;
		
		case "Tuttuat_25":
			dialog.text = "Acho que ele quer ir ao templo dos homens-jaguar, e acredita que o amuleto vai ajudá-lo. Mas posso estar enganado. Ainda assim, a Caleuche sempre se deixa atrair por artefatos da minha terra. Ela navegou perto da ilha onde fica o templo dos homens-jaguar, e navegou pelas costas da minha terra natal.";
			link.l1 = "E onde fica essa ilha?";
			link.l1.go = "Tuttuat_26";
		break;
		
		case "Tuttuat_26":
			dialog.text = "Primeiro você encontra o crânio de Yum Cimil e os amuletos. Depois conversamos sobre a ilha.";
			link.l1 = "Certo. Pode me dar uma dica de onde procurar o crânio de jade?";
			link.l1.go = "Tuttuat_27";
		break;
		
		case "Tuttuat_27":
			dialog.text = "Não sei. Mas está aqui, no Caribe. E amuletos, também. Pergunte. Procure. Encontre.";
			link.l1 = "Heh... Tudo bem, eu vou tentar.";
			link.l1.go = "Tuttuat_28";
		break;
		
		case "Tuttuat_28":
			dialog.text = "E você, tome cuidado, capitão branco. O Caleuche sente os itens de Chavin. Quando tiver o amuleto, ela vai te procurar. Se te encontrar, fuja, e rápido. Se ela te pegar, você está morto.";
			link.l1 = "Esse navio maldito é incrivelmente rápido! É pelo menos duas vezes mais veloz que qualquer outro que já vi. Mas percebi que ele sofre quando navega contra o vento.";
			link.l1.go = "Tuttuat_29";
		break;
		
		case "Tuttuat_29":
			dialog.text = "O Caleuche é amaldiçoado – por isso ele é tão rápido. Difícil de escapar. Você precisa de um navio que consiga ser mais rápido que o Caleuche. Ou vai acabar morto. Quando encontrar o amuleto, traga para mim. Não deixe o amuleto no navio.";
			link.l1 = "Já entendi. Obrigado pela sua história, grande xamã. Agora preciso ir.";
			link.l1.go = "Tuttuat_31";
		break;
		
		case "Tuttuat_31":
			dialog.text = "Estou pedindo aos espíritos que te ajudem e te salvem do Caleuche.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_32";
		break;
		
		case "Tuttuat_32":
			DialogExit();
			LocatorReloadEnterDisable("Shore27", "boat", false);
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "mayak"; 
			AddQuestRecord("Caleuche", "6");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Amuletmaster") && pchar.questTemp.Caleuche.Amuletmaster == "Santiago_Lightman") {AddLandQuestMark(characterFromId("Santiago_Lightman"), "questmarkmain");}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Amuletmaster") && pchar.questTemp.Caleuche.Amuletmaster == "BasTer_Lightman") {AddLandQuestMark(characterFromId("BasTer_Lightman"), "questmarkmain");}
		break;
		
		case "Tuttuat_33":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(olhando) Sim, é esse mesmo. O segundo amuleto Chavin. Você manda bem. Ainda falta encontrar outro amuleto.";
			link.l1 = "Eu me lembro disso, xamã. Em breve será seu.";
			link.l1.go = "Tuttuat_34";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_34":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
			AddQuestRecord("Caleuche", "22");
			if (!Caleuche_CheckAmulet())
			{
				if (GetCharacterIndex("Map_Caleuche") != -1)
				{
					sld = characterFromId("Map_Caleuche");
					sld.lifeday = 0;
					Map_ReleaseQuestEncounter("Map_Caleuche");
				}
			}
		break;
		
		case "Tuttuat_35":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Vá, homem branco. Encontre mais um amuleto.";
				link.l1 = "Já consegui, grande xamã. Aqui, dê uma olhada.";
				link.l1.go = "Tuttuat_36";
			}
			else
			{
				dialog.text = "Vá, homem branco. Encontre mais um amuleto.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_35_1";
			}
		break;
		
		case "Tuttuat_35_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
		break;
		
		case "Tuttuat_36":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(olhando) Sim, é esse mesmo. O terceiro amuleto dos Chavins. Você é bom. Encontrou todos os amuletos para passar pelos guerreiros jaguar mortos, servos de Yum Cimil.";
			link.l1 = "Então, pelo que entendi, vou precisar do crânio de jade?";
			link.l1.go = "Tuttuat_37";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_37":
			dialog.text = "Você fala a verdade. O crânio de jade de Yum Cimil. Você precisa levá-lo ao templo de Chavin. Só assim o Caleuche perderá seu poder de uma vez por todas.";
			link.l1 = "Tuttuathapak, por favor, me diga, onde devo procurar? Alguma ideia?";
			link.l1.go = "Tuttuat_38";
		break;
		
		case "Tuttuat_38":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Não. Pense onde foi a última vez que viu o crânio de jade. Para quem você o deu. Comece a procurar por lá.";
				link.l1 = "Certo, grande xamã. Vou fazer tudo o que puder.";
				link.l1.go = "Tuttuat_39";
			}
			else
			{
				dialog.text = "Um feiticeiro branco interessado no crânio de Yum Cimil. Ele está atrás dele. Chegou até a nossa aldeia. Ouvi dizer que esse feiticeiro mora numa casa numa ilha holandesa. Procure o feiticeiro na ilha holandesa, talvez você descubra alguma coisa.";
				link.l1 = "Certo, grande xamã. Vou fazer tudo o que puder.";
				link.l1.go = "Tuttuat_39";
			}
		break;
		
		case "Tuttuat_39":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
			AddQuestRecord("Caleuche", "23");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "I'll start with Curacao, where I handed it over to Solomon. Maybe I'll find some clue - to find out what happened to the skull.";
				else sTemp = "I'll start with visiting Curacao - there I've sold the jade skull to Joachim Merriman.";
			}
			else sTemp = "Tuttuathapak told me, that a 'white warlock' showed interest in the jade skull, and adviced seeking for him on Dutch islands. Who might that be?";
			AddQuestUserData("Caleuche", "sText", sTemp);
			if (GetCharacterIndex("Map_Caleuche") != -1)
			{
				sld = characterFromId("Map_Caleuche");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter("Map_Caleuche");
			}
			pchar.questTemp.Caleuche = "skul";
			pchar.quest.Caleuche_villemstad.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstad.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Caleuche_villemstad.function = "Caleuche_CreateMonk";
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Tuttuat_40":
			dialog.text = "Vá, homem branco. Encontre o crânio de jade de Yum Cimil.";
			if (pchar.questTemp.Caleuche == "island")
			{
				link.l1 = "Está aqui, grande xamã, dê uma olhada.";
				link.l1.go = "Tuttuat_45";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Tuttuat_40_1";
			}
		break;
		
		case "Tuttuat_40_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_41":
			dialog.text = "Vá, homem branco. Encontre o crânio de jade de Yum Cimil.";
			link.l1 = "Receio que não vou conseguir fazer isso. Encontrei o feiticeiro, mas no último momento ele escapou com o crânio. Não faço a menor ideia de onde ele possa estar agora.";
			link.l1.go = "Tuttuat_42";
		break;
		
		case "Tuttuat_42":
			dialog.text = "Isto é muito ruim, homem branco. Agora você não vai passar pelo templo e não vai derrotar o Caleuche. Não te dou presente nenhum. Agora vá embora.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_43";
		break;
		
		case "Tuttuat_43":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_44";
		break;
		
		case "Tuttuat_44":
			dialog.text = "Vá embora agora, homem branco.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_44_1";
		break;
		
		case "Tuttuat_44_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_45":
			dialog.text = "(olhando) Sim, é essa mesmo. Muito bonita. E muito assustadora.";
			link.l1 = "Sure... But what's more interesting – I crossed the entire Caribbean Sea from Cuba to Dominica, and the Caleuche never tried to attack me when I had this skull; I didn't even see it. Yet when I was carrying amulets to you, it constantly hunted me down – as soon as I set sail, it found me within a few hours.";
			link.l1.go = "Tuttuat_46a";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_46a":
			dialog.text = "Acho que o Caleuche tem medo do crânio, ou então não consegue senti-lo. Não vejo outra explicação. Talvez Yum Cimil tenha tornado o crânio de jade muito perigoso para o Caleuche - além da maldição. Talvez seja por isso que o capitão queria tanto pegar os três amuletos do meu povo. Para obter sabedoria sobre como controlar o feitiço de Yum Cimil.";
			link.l1 = "Então, enquanto eu tiver o crânio de jade a bordo do meu navio, não preciso temer os ataques do Caleuche?";
			link.l1.go = "Tuttuat_46b";
		break;
		
		case "Tuttuat_46b":
			dialog.text = "Exatamente, cara-pálida. Você está vendo com seus próprios olhos.";
			link.l1 = "Muito bom! Então, posso assumir o comando de um navio grande, contratar uma tripulação decente e preparar uma recepção à altura para aquele morto-vivo ambulante, quando o feitiço for quebrado, sem medo de que ele me intercepte antes...";
			link.l1.go = "Tuttuat_46c";
		break;
		
		case "Tuttuat_46c":
			dialog.text = "";
			link.l1 = "...sobre aquele feitiço, aliás - onde devo levar o crânio de jade?";
			link.l1.go = "Tuttuat_46";
		break;
		
		case "Tuttuat_46":
			dialog.text = "Você deve levar isso ao templo de Chavin e terminar sua jornada. Quero te contar uma história. Está pronto para ouvir, homem branco?";
			link.l1 = "Meus ouvidos estão sempre abertos à sua sabedoria, Tuttuathapak.";
			link.l1.go = "Tuttuat_47";
		break;
		
		case "Tuttuat_47":
			dialog.text = "Como dizem as lendas dos meus ancestrais, há muito tempo, quando os homens de rosto pálido ainda não tinham chegado à nossa terra, o grande chefe dos Chavins construiu uma canoa enorme e enviou um grupo de guerreiros para a terra das muitas ilhas. O filho do grande chefe os liderava, e entre eles estava um dos grandes xamãs. Na terra das muitas ilhas, encontraram um lugar deserto e fundaram um assentamento, erguendo um grande templo para Yum Cimil, que só nossos grandes ancestrais poderiam ter construído\nMensageiros voltaram com boas notícias, mas ninguém jamais viu de novo o filho do chefe, nem o xamã, nem os guerreiros. Diz a lenda que eles ficaram lá para viver, mas o mais sábio dos xamãs falou com os espíritos e disse que ninguém mais vivia lá, e que Yum Cimil reinava sobre aquela terra\nA terra das muitas ilhas é o Caribe, homem branco. O templo de Yum Cimil está numa ilha onde não vivem nem homens brancos nem índios. Só os servos de Yum Cimil, os Chavinavi, ainda guardam os corredores do templo.";
			link.l1 = "E onde fica essa ilha?";
			link.l1.go = "Tuttuat_48";
		break;
		
		case "Tuttuat_48":
			dialog.text = "Pelo que entendi da história, é uma ilha pequena, situada a partir da ilha com esta vila na direção que os rostos pálidos chamam de 'norte', no meio de três ilhas, e no quarto lado há a grande água — o oceano.";
			link.l1 = "Hmm... Ao norte de Dominica, dentro de um triângulo de ilhas, bem na beira do oceano? Poxa, isso é um bom pedaço de mar! Como é que vou encontrar uma ilhota lá que ninguém nunca ouviu falar?";
			link.l1.go = "Tuttuat_49";
		break;
		
		case "Tuttuat_49":
			dialog.text = "Não posso dizer com certeza. Mas conheço outra história. Talvez você já tenha ouvido ela dos seus irmãos. Cerca de vinte invernos atrás, um homem branco encontrou aquela ilha. Com uma mulher e um velho, ele entrou no templo de Yum Cimil e levou um artefato poderoso – o Orbe do Sol Nascente. Às margens da ilha, o capitão de rosto pálido foi atacado pelo Caleuche\nO homem de rosto pálido era astuto. Ele cegou o capitão e a tripulação do Caleuche com o sol nascente. A maldição do Caleuche enfraqueceu, e o capitão afundou o navio, mas o Orbe do Sol Nascente se desfez. Se você encontrar esse homem de rosto pálido, ele vai te contar onde fica a ilha.";
			if (CheckAttribute(pchar, "questTemp.NatanStory")) link.l1 = "Ha! Acho que sei quem é esse 'homem de rosto pálido'... As histórias são muito parecidas. Então, o Caleuche afundou?";
			else link.l1 = "Hmm... Então, o Caleuche afundou?";
			link.l1.go = "Tuttuat_50";
		break;
		
		case "Tuttuat_50":
			dialog.text = "Sim, mas a maldição os protege da morte. Eles consertaram e continuaram sua jornada eterna.";
			link.l1 = "Certo, entendi. Mas o que eu devo fazer no templo? Onde devo colocar o crânio? Como posso derrotar os guerreiros jaguar que o guardam? Se eles forem Chavinavi como aqueles invocados pelo feiticeiro Merriman, seria loucura ir lá sozinho – cada um deles é tão forte quanto dez soldados.";
			link.l1.go = "Tuttuat_51";
		break;
		
		case "Tuttuat_51":
			dialog.text = "Eles não são. Os Chavinavi invocados pelo feiticeiro branco com o crânio são fracos. Muito mais fracos do que aqueles invocados pelo próprio Yum Cimil. Você nunca conseguirá feri-los, e eles te matam com um único toque de sua arma.";
			link.l1 = "Espera aí – e como esse 'homem de rosto pálido' conseguiu entrar no templo e roubar o artefato?";
			link.l1.go = "Tuttuat_52";
		break;
		
		case "Tuttuat_52":
			dialog.text = "Antes daquele primeiro homem de rosto pálido entrar no templo, ele era protegido pelos espíritos dos ancestrais mortos. O homem de rosto pálido era um guerreiro forte e os derrotou. Quando ele roubou o orbe do sol nascente, Yum Cimil ficou furioso. Ele enviou fogo e enxofre contra o homem de rosto pálido e quase destruiu o templo, mas ele escapou com o artefato. Agora Yum Cimil convocou guerreiros-jaguares invencíveis para proteger o templo.";
			link.l1 = "Glorioso! E como é que eu vou entrar sem ser visto, então?";
			link.l1.go = "Tuttuat_53";
		break;
		
		case "Tuttuat_53":
			dialog.text = "I help you, white man. I give you two Chavin amulets you bring me. I will speak to the ancestor spirits and empower the amulet. When you have one with you, you can fight jaguar warriors like common soldiers; you will be like one of them, though very strong. The amulet will protect you and give your weapon the power to harm the Chavinavi of the temple.";
			link.l1 = "Tem certeza de que os amuletos vão ajudar?";
			link.l1.go = "Tuttuat_54";
		break;
		
		case "Tuttuat_54":
			dialog.text = "I know. I speak to the ancestors. I am a great shaman. You trust me. You take two amulets. One protects. The other empowers your weapon. You must use one amulet. Which one - you choose. If you do not wear an amulet, you will perish to the jaguar warriors\nAnd remember, at midnight Yum Cimil brings back to life all the warriors you kill. You must figure out the timing so you do not fight them twice, or do so; the spirits tell me that you could.";
			link.l1 = "Entendi.";
			link.l1.go = "Tuttuat_55";
		break;
		
		case "Tuttuat_55":
			dialog.text = "Pegue os amuletos. Aqui estão. Lembre-se, o poder deles tem limites. Ele enfraquece em uma lua. Lembre-se do que eu disse, você não pode controlar esse poder. Só o grande xamã da nossa tribo pode usá-lo.";
			link.l1 = "Eu me lembro. Então, eu só tenho uma lua? Um mês?";
			link.l1.go = "Tuttuat_56";
		break;
		
		case "Tuttuat_56":
			dialog.text = "Sim. Quando você chegar ao templo de Yum Cimil, precisa encontrar o altar e uma grande estátua do Condor lá dentro. Essa é a parte mais importante do templo. Ali você coloca o crânio de jade de Yum Cimil, e a maldição será quebrada do Caleuche. Quando ele te atacar de novo, você vai derrotá-lo como um homem comum. Depois, traga para mim o amuleto que ele tirou de você.";
			link.l1 = "Condor? O que foi?";
			link.l1.go = "Tuttuat_57";
		break;
		
		case "Tuttuat_57":
			dialog.text = "Condor é uma grande ave que vive nas montanhas da minha terra natal. Em memória de casa, meus ancestrais construíram uma estátua do Condor perto do santuário.";
			link.l1 = "Tá bom, eu vou procurar por isso...";
			link.l1.go = "Tuttuat_58";
		break;
		
		case "Tuttuat_58":
			dialog.text = "Tome cuidado. Muitos perigos espreitam no templo além dos guerreiros jaguar.";
			link.l1 = "Que perigos?";
			link.l1.go = "Tuttuat_59";
		break;
		
		case "Tuttuat_59":
			dialog.text = "Eu não sei ao certo. Veja você mesmo. Pode ser uma armadilha, ou só confusão. Entrar no santuário é difícil. A entrada está selada, e você precisa encontrar um jeito de abri-la. Meus ancestrais não eram apenas grandes guerreiros e xamãs, mas também grandes construtores. Para abrir, você vai precisar pensar.";
			link.l1 = "Heh! Parece assustador, mas que venham todos! Não vou perder tempo. Vou zarpar agora mesmo!";
			link.l1.go = "Tuttuat_60";
		break;
		
		case "Tuttuat_60":
			dialog.text = "Vá, guerreiro branco. Vou invocar espíritos para ajudá-lo contra os guerreiros jaguar e o Caleuche. Lembre-se, se usar amuletos posso ajudar, caso contrário, você vai perecer";
			link.l1 = "Obrigado, grande xamã... Eu vou cumprir com isso.";
			link.l1.go = "Tuttuat_61";
		break;
		
		case "Tuttuat_61":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
			npchar.greeting = "Tuttuat_3";
			Log_Info("You have received two amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "kaleuche_amulet2");
			GiveItem2Character(pchar, "kaleuche_amulet3");
			// преобразуем амулеты
			ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_sword");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_shield");
			sld = ItemsFromID("kaleuche_amulet2");
			AddDescriptor(sld, M_AMULET_TYPE, AMULET_PAGAN);
			aref modifier = AddCallback(sld, CT_COMMON, "KaleucheAmuletAttack");
			modifier.arg0 = 0.25;
			sld.picIndex = 13;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			sld = ItemsFromID("kaleuche_amulet3");
			AddDescriptor(sld, M_AMULET_TYPE, AMULET_PAGAN);
			SetModifierFromSource(sld, HAS + M_CANT_BE_POISONED, true, TALISMAN_ITEM_TYPE);
			SetModifier(sld, M_REDUCE_DAMAGE, 0.25);
			sld.picIndex = 14;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			SetFunctionTimerCondition("Caleuche_TuttuatAmuletOver", 0, 0, 30, false); // таймер
			// делаем доступным Хаэль Роа
			n = FindIsland("KhaelRoa");
			Islands[n].visible = true;
			Island_SetReloadEnableGlobal(Islands[n].id, true);
			Islands[n].reload.l1.radius = 150.0;
			Islands[n].reload.l2.label = "Shore64_1";
			Islands[n].reload.l2.name = "reload_2";
			Islands[n].reload.l2.go = "";
			Islands[n].reload.l2.emerge = "";
			Islands[n].reload.l2.radius = 0.0;
			Islands[n].reload.l2.pic = 0;
			Islands[n].reload.l2.tex = "t1";
			pchar.questTemp.Caleuche = "khaelroa";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1 = "location";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1.location = "KhaelRoa_port";
			pchar.quest.Caleuche_khaelroa_arrive.function = "Caleuche_KhaelRoaArrive";
			AddQuestRecord("Caleuche", "34");
			if (CheckAttribute(pchar, "questTemp.NatanStory")) 
			{
				pchar.questTemp.Caleuche.NatanInfo = "true";
				AddQuestUserData("Caleuche", "sText", "But I have a clue: it seems that white captain, who had visited the temple of the Chavins, is none other than my good friend Nathaniel Hawk. I remember him saying that he had a map of that island in Maroon Town. Guess I will pay Nathan a visit.");
			}
			else AddQuestUserData("Caleuche", "sText", "That's a huge area in the sea, but I have no choice. I'll have to scour it entirely. Shaman said North of Dominica, and not too far so I could steadily move North, it might very well be a bit to the East or West. He also mentioned some Captain that destroyed the undead ship maybe I will be lucky and I might find him one day, alas, he said that I have only one month to hold this power or whatever it is, oh well it is what it is, let the search begin!");
		break;
		
		case "Tuttuat_62":
			if (pchar.questTemp.Caleuche == "regard" && CheckCharacterItem(pchar, "kaleuche_amulet1") && CheckCharacterItem(pchar, "kaleuche_amulet2") && CheckCharacterItem(pchar, "kaleuche_amulet3")) 
			{
				dialog.text = "Eu falo com espíritos. Você esteve na ilha, no templo de Yum Cimil. Encontrou o Caleuche e o amuleto?";
				link.l1 = "Você está certo, grande xamã. Encontrei a ilha, entrei no templo e deixei o crânio de jade lá dentro.";
				link.l1.go = "Tuttuat_63";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Vá, guerreiro branco.";
				if (CheckAttribute(pchar, "questTemp.Caleuche.AmuletOver"))
				{
					link.l1 = "Tuttuathapak, veja... Eu não levei o crânio ao templo a tempo, e seus amuletos perderam o poder.";
					link.l1.go = "Tuttuat_82";
				}
				else
				{
					link.l1 = "...";
					link.l1.go = "Tuttuat_62_1";
				}
			}
		break;
		
		case "Tuttuat_62_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
		break;
		
		case "Tuttuat_63":
			npchar.greeting = "Tuttuat_2";
			pchar.quest.Caleuche_TuttuatAmuletOver.over = "yes"; //снять таймер
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet2")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet3")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "Você quebrou a maldição do Caleuche. Ela te procurou depois disso?";
			link.l1 = "Sim. Nós nos conhecemos bem na ilha. Eu a desafiei para um combate e saí vitorioso. Agora estou com todos os três amuletos. Aqui, pegue-os.";
			link.l1.go = "Tuttuat_64";
		break;
		
		case "Tuttuat_64":
			RemoveItems(pchar, "kaleuche_amulet1", 1);
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given three Chavin amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "Você é um guerreiro rápido e forte, homem de pele clara. Tuttuathapak não gosta de homens brancos, mas respeito um guerreiro corajoso e habilidoso. Você foi muito bem. Livrou os mares do Caleuche. Trouxe-me três amuletos. Vou recompensá-lo.";
			link.l1 = "Você prometeu algo sobre 'um poder que eu seria capaz de manter para sempre'?";
			link.l1.go = "Tuttuat_65";
		break;
		
		case "Tuttuat_65":
			dialog.text = "Você fala a verdade. Vou te dar esse poder. Ninguém no Caribe conhece o segredo da planta que eu conheço. Ouça-me, cara-pálida! Na minha casa, há uma planta medicinal. Chamamos ela de Manga Rosa. Já ouviu falar dessa planta?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa.Tell"))
			{
				link.l1 = "Sim. Eu segurei isso nas minhas mãos. Os ciganos demonstram muito interesse por ele. E uma deles, a curandeira Amélia, pode até...";
				link.l1.go = "Tuttuat_66";
			}
			else
			{
				link.l1 = "Não faço ideia...";
				link.l1.go = "Tuttuat_66_1";
			}
		break;
		
		case "Tuttuat_66":
			dialog.text = "Ouvi falar da herbalista Amelia. Ela sabe um pouco, mas não muito. Ela não conhece o segredo da Manga Rosa. Só um grande xamã da minha terra natal, de onde a Manga Rosa foi trazida para cá, pode usar todo o seu poder.";
			link.l1 = "Que poder?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_66_1":
			dialog.text = "Essa erva cresce na minha terra natal, mas também pode ser encontrada no Caribe. É uma planta alta, de verde-claro, com folhas parecidas com uma palma aberta, e um cheiro agradável. Você vai reconhecê-la na hora e não vai confundir com nenhuma outra. Eu conheço os segredos dessa planta. Sei como extrair poder dela.";
			link.l1 = "Eu entendo, mas que tipo de poder?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_67":
			dialog.text = "Eu posso fazer poções de Manga Rosa. Poções muito fortes. Ninguém além de mim no Caribe consegue fazer isso. Minhas poções tornam um homem para sempre mais forte, rápido, inteligente, de olhos mais atentos, mais bonito e mais sortudo. Vou preparar três dessas poções para você.";
			link.l1 = "Muito interessante!";
			link.l1.go = "Tuttuat_68";
		break;
		
		case "Tuttuat_68":
			dialog.text = "Você é um grande guerreiro, então primeiro você precisa de uma poção para ficar mais resistente e outra para ficar mais ágil. E você vai escolher a terceira poção depois que eu fizer as duas primeiras. Mas você precisa me trazer Manga Rosa para prepará-las – eu não tenho nenhuma.";
			link.l1 = "Onde devo procurar pela Manga Rosa?";
			link.l1.go = "Tuttuat_69";
		break;
		
		case "Tuttuat_69":
			dialog.text = "Manga Rosa é uma erva rara no Caribe. Ela cresce onde quase ninguém passa. Gente tola colhe, seca e fuma. Gente muito tola. NÃO FUME ISSO! É um desperdício do seu poder... Procure por selvas e enseadas, lugares secretos onde os tolos não vão. Preste atenção. Para cada poção eu preciso de cinco caules de Manga Rosa.";
			link.l1 = "Certo, grande xamã. Voltarei quando eu tiver Manga Rosa suficiente.";
			link.l1.go = "Tuttuat_70";
		break;
		
		case "Tuttuat_70":
			dialog.text = "Vá, guerreiro branco. Traga-me Manga Rosa. Você não vai se arrepender. Minhas poções são as melhores. Vou pedir aos espíritos para te ajudar na sua busca.";
			link.l1 = "Obrigado! Até logo, xamã!";
			link.l1.go = "Tuttuat_71";
		break;
		
		case "Tuttuat_71":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			pchar.questTemp.Caleuche = "mangarosa";
			pchar.questTemp.Caleuche.Mangarosa = 0;
			AddQuestRecord("Caleuche", "41");
		break;
		
		case "Tuttuat_72":
			dialog.text = "Você trouxe cinco caules de Manga Rosa para a poção?";
			if (GetCharacterItem(pchar, "cannabis7") >= 5)
			{
				link.l1 = "Sim. Aqui estão as cinco plantas que você precisa.";
				link.l1.go = "Tuttuat_73";
			}
			link.l2 = "Ainda não, grande xamã. Minha busca continua...";
			link.l2.go = "Tuttuat_72_1";
		break;
		
		case "Tuttuat_72_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
		break;
		
		case "Tuttuat_73":
			RemoveItems(pchar, "cannabis7", 5);
			switch (sti(pchar.questTemp.Caleuche.Mangarosa))
			{
				case 0:
					dialog.text = "Muito bem. Venha amanhã, quando o sol se pôr. Vou preparar poções para você que vão aumentar sua reação e destreza.";
					link.l1 = "Certo, xamã. Eu volto amanhã à noite.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 1;
				break;
				
				case 1:
					dialog.text = "Muito bem. Venha amanhã, quando o sol se pôr. Vou preparar poções para aumentar sua resistência.";
					link.l1 = "Certo, xamã. Eu volto amanhã à noite.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 2;
				break;
				
				case 2:
					dialog.text = "Muito bem. Qual poção você escolhe? Poção de força, visão aguçada, inteligência, beleza ou sorte?";
					link.l1 = "Poção de força.";
					link.l1.go = "Tuttuat_77_1";
					link.l2 = "Poção da visão aguçada.";
					link.l2.go = "Tuttuat_77_2";
					link.l3 = "Poção de inteligência.";
					link.l3.go = "Tuttuat_77_3";
					link.l4 = "Poção da beleza.";
					link.l4.go = "Tuttuat_77_4";
					link.l5 = "Poção da sorte.";
					link.l5.go = "Tuttuat_77_5";
				break;
			}
		break;
		
		case "Tuttuat_74":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1 = "Timer";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.hour  = 19.0;
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.function = "Caleuche_MangarosaPotion";
		break;
		
		case "Tuttuat_75":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Potion"))
			{
				sTemp = "";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1) sTemp = "  It make your movements faster, and you better fight with fine light weapons.";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2) sTemp = "  It make you more hardy in long journeys, and you better fight with sharp sabers.";
				dialog.text = "A poção está pronta, guerreiro de rosto pálido. Pegue."+sTemp+"";
				link.l1 = "Obrigado, grande xamã.";
				link.l1.go = "Tuttuat_76";
			}
			else
			{
				dialog.text = "Ainda não está pronto, homem branco. Volte mais tarde. Não me incomode.";
				link.l1 = "Tudo bem...";
				link.l1.go = "Tuttuat_75_1";
			}
		break;
		
		case "Tuttuat_75_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
		break;
		
		case "Tuttuat_76":
			if (sti(pchar.questTemp.Caleuche.Mangarosa) > 2)
			{
				dialog.text = "Preparei todas as poções que prometi para você. Você vai ficar mais forte. Está feliz?";
				link.l1 = "Sim, grande xamã. Realmente foi uma recompensa digna.";
				link.l1.go = "Tuttuat_78";
			}
			else
			{
				dialog.text = "Você encontra mais cinco talos de Manga Rosa, traga para mim. Eu faço outra poção para você.";
				link.l1 = "Vou trazer mais deles para você. Até logo!";
				link.l1.go = "Tuttuat_77";
			}
		break;
		
		case "Tuttuat_77":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1)
			{
				ChangeItemDescribe("kaleuche_amulet1", "itmdescr_kaleuche_amulet1_potion");
				sld = ItemsFromID("kaleuche_amulet1");
				sld.name = "itmname_kaleuche_amulet1_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet1");
			}
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2)
			{
				ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_potion");
				sld = ItemsFromID("kaleuche_amulet2");
				sld.name = "itmname_kaleuche_amulet2_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet2");
			}
		break;
		
		case "Tuttuat_77_1":
			dialog.text = "Venha amanhã, como sempre. Vou preparar uma poção para te deixar mais forte, e você vai lutar melhor com um machado grande.";
			link.l1 = "Certo.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 31;
		break;
		
		case "Tuttuat_77_2":
			dialog.text = "Venha amanhã, como sempre. Vou preparar uma poção para deixar seus olhos atentos, assim você verá cada alvo, e vai atacar melhor com armas flamejantes que rugem.";
			link.l1 = "Tudo bem.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 32;
		break;
		
		case "Tuttuat_77_3":
			dialog.text = "Venha amanhã, como sempre. Vou preparar uma poção para te deixar mais esperto, e é melhor você se esconder dos seus inimigos.";
			link.l1 = "Certo.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 33;
		break;
		
		case "Tuttuat_77_4":
			dialog.text = "Venha amanhã, como sempre. Vou preparar uma poção pra te deixar mais bonito, e você vai ser melhor em convencer as pessoas.";
			link.l1 = "Tudo bem.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 34;
		break;
		
		case "Tuttuat_77_5":
			dialog.text = "Venha amanhã, como sempre. Vou preparar uma poção para te trazer mais sorte, e você terá boa fortuna.";
			link.l1 = "Certo.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 35;
		break;
		
		case "Tuttuat_78":
			dialog.text = "Fico feliz que você goste da minha arte, a arte de um grande xamã.";
			link.l1 = "Me diz, Tuttuathapak, pra que você precisava desses três amuletos? Só por curiosidade...";
			link.l1.go = "Tuttuat_79";
		break;
		
		case "Tuttuat_79":
			dialog.text = "Você já pode sentir o poder desses dois amuletos. Os espíritos vão me ajudar a fortalecê-los, e os três amuletos juntos vão conceder a grande sabedoria xamânica e a iluminação dos meus ancestrais, os grandes Chavins.";
			link.l1 = "Entendi. Certo, obrigado mais uma vez pelas suas poções incríveis. Você é realmente um grande xamã. Agora está na hora de eu partir. Adeus, Tuttuathapak, espero te ver novamente.";
			link.l1.go = "Tuttuat_80";
		break;
		
		case "Tuttuat_80":
			dialog.text = "Adeus, guerreiro branco. Não precisa mais me procurar. Vou me recolher, buscar a sabedoria dos meus ancestrais. Que os espíritos te acompanhem nas suas jornadas!";
			link.l1 = "Então... hah... que os espíritos também guiem o seu caminho, grande xamã. Adeus...";
			link.l1.go = "Tuttuat_81";
		break;
		
		case "Tuttuat_81":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			GiveItem2Character(pchar, "kaleuche_amulet3");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_potion");
			sld = ItemsFromID("kaleuche_amulet3");
			sld.name = "itmname_kaleuche_amulet3_potion";
			sld.groupID = SPECIAL_ITEM_TYPE;
			sld.picIndex = 15;
			sld.picTexture = "ITEMS_35";
			sld.price = 0;
			sld.Weight = 1.0;
			sld.reaction = sti(pchar.questTemp.Caleuche.Mangarosa);
			sld.ItemType = "SUPPORT";
			i = sti(sld.reaction);
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet"+i+"_potion");
			AddQuestRecord("Caleuche", "42");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			DeleteAttribute(pchar, "questTemp.Caleuche.Mangarosa");
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
		break;
		
		case "Tuttuat_82":
			Log_Info("You have given amulets");
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			dialog.text = "Você me deixa triste, cara-pálida. Fiz um ritual com os espíritos para dar poder a esses amuletos, e você desperdiçou isso. Estou triste. Agora vá. Tuttuathapak não tem mais nada a dizer para você.";
			link.l1 = "Desculpe, eu só tive muito azar... Fazer o quê. Adeus, xamã.";
			link.l1.go = "Tuttuat_83";
		break;
		
		case "Tuttuat_83":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Caleuche", "43");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			sld = ItemsFromID("SkullAztec");
			sld.price = 10000;
		break;

		// капитан Калеуче
		case "CaleucheCap":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_01.wav");
			dialog.text = "É tudo em vão, marinheiro. Você não vai me vencer. E todos os meus homens caídos no convés vão juntar seus ossos e se levantar de novo antes do amanhecer. Não podemos ser mortos, pois a morte nos abandonou para sempre.";
			link.l1 = "Maldição! Você está morto ou vivo? Mais provável que ainda esteja vivo – os mortos geralmente ficam quietos e não balançam espadas. Mas quem é você, e por que atacou meu navio?";
			link.l1.go = "CaleucheCap_1";
		break;
		
		case "CaleucheCap_1":
			dialog.text = "Eu sou Balthazar de Cordes, do Coração Voador. Covardes miseráveis, que nada sabem sobre mim, me chamam de Van der Decken, capitão do Holandês Voador. Mas isso não importa. O que importa é que você está com um amuleto, e eu vou pegá-lo agora. Eu preciso dele! Eu sinto isso! O grande amuleto dos Chavins, um dos três, finalmente será meu! Ajoelhe-se diante de mim, mortal! E talvez eu torne sua morte indolor!";
			link.l1 = "Vá para o inferno, cadáver!";
			link.l1.go = "CaleucheCap_2";
		break;
		
		case "CaleucheCap_2":
			DialogExit();
			npchar.MultiFighter = 4.0;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(pchar, 10, true, "Caleuche_GhostshipGetOut");
		break;
		
		case "CaleucheCap_3":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_02.wav");
			dialog.text = "Eu não acredito! Faz tanto tempo desde a última vez que vi meu próprio sangue ou senti alguma dor... COMO?!";
			link.l1 = "Desta vez você perdeu, Balthazar de Cordes. Eu conheço sua história. O crânio de jade foi devolvido ao templo dos Chavins, e a maldição de Yum Cimil não pesa mais sobre você nem sobre seus homens. Você não vai mais trazer seus marinheiros de volta à vida.";
			link.l1.go = "CaleucheCap_4";
		break;
		
		case "CaleucheCap_4":
			dialog.text = "Ah, então você se acha um redentor, é isso? Não! Balthazar de Cordes vai lutar até o fim pelo pouco de vida que lhe resta!";
			link.l1 = "A última jornada do Coração Voador termina aqui, em Khael Roa. E você não vai erguer seu navio do fundo do mar, como fez há vinte e cinco anos.";
			link.l1.go = "CaleucheCap_5";
		break;
		
		case "CaleucheCap_5":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_03.wav");
			dialog.text = "Falcão! Vinte e cinco anos se passaram, e ainda me lembro como se fosse ontem. O brilho daquele orbe que nos cegou e partiu meu navio ao meio. Aquela foi a primeira e última derrota do Coração Voador e de Balthazar de Cordes... Então vamos cruzar as espadas uma última vez, capitão! Morrer em batalha é leve e bem-vindo!";
			link.l1 = "...";
			link.l1.go = "CaleucheCap_6";
		break;
		
		case "CaleucheCap_6":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Caleuche_ChangeShip");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Caleuche_Alonso_1":
			dialog.text = "A banheira foi limpa da imundície, capitão. Desta vez, os mortos ficaram onde estavam. Mas o navio em si... não faço ideia de como ainda está flutuando.";
			link.l1 = "A maldição estava mantendo ela de pé, Alonso. Mas agora isso acabou.";
			link.l1.go = "Caleuche_Alonso_2";
		break;
		
		case "Caleuche_Alonso_2":
			dialog.text = "Quais são suas ordens? Vamos incendiar o navio e acabar logo com isso?";
			link.l1 = "Vou pensar nisso. Mesmo caindo aos pedaços, o 'Coração Voador' quase transformou nosso navio em uma peneira.";
			link.l1.go = "Caleuche_Alonso_3";
		break;

		case "Caleuche_Alonso_3":
			dialog.text = "Poder de fogo é algo que esse navio tem de sobra, maldita seja três vezes... O que vim dizer é o seguinte - temos um marinheiro na tripulação, o Jacques...";
			link.l1 = "Jacques Trudeau? Eu me lembro dele. Ele entrou para o nosso grupo recentemente, não foi?";
			link.l1.go = "Caleuche_Alonso_4";
		break;

		case "Caleuche_Alonso_4":
			dialog.text = "Então, capitão. O negócio é o seguinte: aquele malandro tem um faro incrível pra coisas de valor – incrível mesmo. Assim que os mortos-vivos ficaram imóveis, ele pulou em um dos beliches, se enfiou debaixo – e puxou um baú. E dentro do baú – cinco mil dobrões!";
			link.l1 = "Cinco mil? Hm... Parece que Balthazar de Cordes e sua tripulação realmente acreditaram que poderiam se livrar da maldição. Encheram os bolsos de ouro, sonhando com uma vida fácil... quando tudo isso acabasse.";
			link.l1.go = "Caleuche_Alonso_5";
		break;
		
		case "Caleuche_Alonso_5":
			dialog.text = "Nossa tripulação também não se importaria de viver assim, Capitão... Se você compartilhar com os rapazes, eles nunca vão esquecer. Mas se não fizer isso – eles vão lembrar.";
			link.l1 = "Você tem razão, Alonso. Devemos agradar um pouco a tripulação – eles mereceram. Entregue metade a eles, e Jacques – dê-lhe uma semana de folga das vigias. Em vez de grogue, hoje permito que sirvam rum. Mas mantenha-se alerta – você sabe que o mar não perdoa erros.";
			link.l1.go = "Caleuche_Alonso_6";
			link.l2 = "Hm... Talvez você tenha razão, Alonso. A tripulação merece relaxar um pouco. Dê a eles um quarto da parte. E certifique-se de que esses bêbados não comecem a festa antes de ancorarmos em algum porto.";
			link.l2.go = "Caleuche_Alonso_7";
			link.l3 = "Para que esses vagabundos se espalhem por tavernas e bordéis logo no primeiro porto? Não vou perder um mês caçando cada um deles. O salário que pago já basta. E traga os dobrões aqui. Não quero que ninguém tenha a ideia de ficar com eles.";
			link.l3.go = "Caleuche_Alonso_8";
		break;
		
		case "Caleuche_Alonso_6":
			dialog.text = "Pode deixar, capitão. E não se preocupe, os rapazes nunca vão te decepcionar.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_2");
		break;
		
		case "Caleuche_Alonso_7":
			dialog.text = "Sim, Capitão. Eu sei como manter aqueles demônios na linha – pode contar comigo.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_3");
		break;
		
		case "Caleuche_Alonso_8":
			dialog.text = "Como quiser, capitão. A tripulação, claro, esperava por mais... mas quem manda aqui é você, a decisão é sua.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_4");
		break;
		
		// --> // наш матрос на берегу
		case "on_coast":
			dialog.text = "Finalmente, você acordou, capitão... Como está se sentindo?";
			link.l1 = "Maldição, o que aconteceu? Minha cabeça está explodindo de dor...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Quando entramos na cabine do capitão, você estava caído no chão, ainda sem se mexer. Os homens te levantaram e te arrastaram para o nosso navio – e foi por pouco, porque os mortos que estavam deitados no convés começaram a se levantar de novo\nSantíssima Virgem e todos os Santos! Cortamos as amarras às pressas e tentamos zarpar, mas uma salva do navio deles logo transformou nossa velha embarcação em pedaços e perdemos o controle dela. Depois eles içaram as velas e sumiram num piscar de olhos\nNosso navio encalhou, e todos que conseguiram sobreviver chegaram à costa num bote. Muitos bons homens morreram hoje... se ao menos tivéssemos ficado a bordo... Mas tínhamos certeza de que a tempestade acabaria de vez com o navio.";
			link.l1 = "Não foi culpa de vocês, senhores. Foi a decisão certa. Obrigado, vou me lembrar disso.";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Arrastamos você para o barco e depois trouxemos você para a terra. Você estava quase morto...";
			link.l1 = "Eu te devo a minha vida. Quanto tempo eu fiquei aqui, desacordado?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Por um dia inteiro. Cuidamos dos seus ferimentos, te demos remédio e até um pouco de rum. Logo você vai ficar bem.";
			link.l1 = "Com certeza não vou morrer desta vez. Embora eu não esteja me sentindo muito bem...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Isso com certeza... Era o Holandês Voador, Capitão? Por que eles atacaram a gente? E por que não atiraram antes de abordar, mas quase afundaram nosso navio com um único disparo depois?";
			link.l1 = "O capitão deles precisava do amuleto, sobre o qual eu tinha falado com Tuttuathapak, um xamã indígena. Por isso não nos afundaram de imediato, mas assim que o líder deles pegou o amuleto, se livraram de nós sem demora... Que pesadelo! Um navio tripulado por mortos! Difícil de acreditar...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Sim, agora foi a nossa vez de encontrar o Holandês Voador. Quando eu tiver a chance, vou à igreja, acendo uma vela pela minha salvação milagrosa e faço uma oração ao nosso Senhor...";
			link.l1 = "Eu também... Acho que sim. Mas primeiro vou voltar para aquela aldeia. Preciso contar tudo ao Tuttuathapak. Aquele navio maldito nos atacou por causa do amuleto! Tenho certeza de que aquele demônio de pele vermelha tinha alguma ideia do porquê, diabos, aqueles mortos-vivos poderiam precisar dele.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Certo. Mas tome cuidado, capitão, seus ferimentos mal cicatrizaram. Pelo menos leve alguém com você, por precaução.";
			link.l1 = "Eu vou tomar cuidado, prometo. Obrigado por não me abandonar!";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "Do que você está falando, capitão! Iríamos até o fim do mundo por você e enfrentaríamos milhares de mortos-vivos! É uma pena danada termos perdido tanto, mas essa história vai virar lenda.";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		
		// Фергус Хупер
		case "fergus":
			dialog.text = "Ei! Ainda não consegui juntar peles de cobra suficientes pra te vender, então cai fora!";
			link.l1 = "Hmm... Você é Fergus Hooper?";
			link.l1.go = "fergus_1";
			DelLandQuestMark(npchar);
		break;
		
		case "fergus_1":
			dialog.text = "Não, meu nome é Tuttuathapak, e eu vou te amaldiçoar se você não sumir daqui agora mesmo. Então é melhor se apressar, ou você vai...";
			link.l1 = "...perder a cabeça, queimar meu próprio navio, e meus marinheiros vão me matar e levar tudo o que tenho. Certo?";
			link.l1.go = "fergus_2";
		break;
		
		case "fergus_2":
			sld = characterFromId(pchar.questTemp.Caleuche.Amuletmaster);
			dialog.text = "Argh... Mas que diabos, quem é você!? Como você...";
			link.l1 = "Temos um amigo em comum, Fergus. Ele é o faroleiro, e o nome dele é "+GetFullName(sld)+". Ele me falou sobre você e me mandou te procurar. Aliás, eu conheço o Xamã Tuttuathapak pessoalmente, então sua piada não colou, desculpe. Olha, não estou aqui pra arrumar confusão. Quero comprar algo de você, e não são peles de cobra.";
			link.l1.go = "fergus_3";
		break;
		
		case "fergus_3":
			dialog.text = "Ah, então você conhece meu velho amigo! Como ele está? Já morreu de tédio naquele farol? Por favor, sente-se, marinheiro, tome um drink comigo!";
			link.l1 = "Me desculpe, Fergus, mas realmente não tenho muito tempo. Ouça, eu preciso daquele amuleto indígena, um daqueles que seu falecido capitão trouxe do continente com Tuttuathapak. Eu pago bem por ele, e você se livra de um objeto perigoso.";
			link.l1.go = "fergus_4";
		break;
		
		case "fergus_4":
			dialog.text = "E o que tem de tão perigoso nisso? Até agora não vi nenhum mal nisso. É só uma pedra inútil";
			link.l1 = "Isso é porque você não navega mais pelos mares. Eu também tinha um amuleto parecido até pouco tempo atrás. Um navio fantasma está caçando essas coisas.";
			link.l1.go = "fergus_5";
		break;
		
		case "fergus_5":
			dialog.text = "Tá brincando, camarada? Será que conhecer o Tuttuathapak te deixou meio fora de si? Cuidado, capitão, aquele demônio de pele vermelha vai devorar sua mente...";
			link.l1 = "Acredite ou não, mas estou dizendo a verdade. Eu mesmo não acreditaria se não tivesse visto com meus próprios olhos. Posso jurar pelo Livro, ou você pode perguntar para quem estava comigo. Mal sobrevivi depois daquele encontro com o Caleuche.";
			link.l1.go = "fergus_6";
		break;
		
		case "fergus_6":
			dialog.text = "O Caleuche?";
			link.l1 = "Bem, a maioria chama de Holandês Voador, mas o nome verdadeiro é Coração Voador. Tanto faz. Só me venda esse amuleto. Não serve pra nada pra você mesmo, eu sei.";
			link.l1.go = "fergus_7";
		break;
		
		case "fergus_7":
			dialog.text = "Isso mesmo. É só um bibelô inútil, embora bem bonito. Olha, eu teria vendido pra você sem pensar duas vezes, mas acontece que eu já não o tenho mais. Foi roubado da minha cabana junto com outras coisas, enquanto eu estava caçando na selva. Isso aconteceu faz pouco tempo, cerca de um mês atrás. Desculpe, mas não posso te ajudar com isso.";
			link.l1 = "E quem roubou?";
			link.l1.go = "fergus_8";
		break;
		
		case "fergus_8":
			dialog.text = "Você realmente acha que eu estaria sentado aqui se soubesse quem saqueou minha casa? Tem uma quadrilha de ladrões e bandidos agindo nos arredores de Belize, e eles têm informantes na cidade. Bom, pelo menos é isso que o comandante pensa. Eu tenho certeza de que foram eles.";
			link.l1 = "O comandante sabe dos bandidos e mesmo assim não faz nada?";
			link.l1.go = "fergus_9";
		break;
		
		case "fergus_9":
			dialog.text = "Se ele está fazendo alguma coisa ou não, eu não sei. A única coisa que eu sei com certeza é que meus pertences sumiram, e o seu amuleto precioso foi junto. Tente encontrar esses bandidos – talvez você ache o amuleto nos bolsos deles. É pouco provável que tenham conseguido vender – mercadores não se interessam por esse tipo de coisa.";
			link.l1 = "Certo, vou falar com o comandante. Boa sorte, Fergus!";
			link.l1.go = "fergus_10";
		break;
		
		case "fergus_10":
			DialogExit();
			AddQuestRecord("Caleuche", "9");
			pchar.questTemp.Caleuche.Bandos = "start"; 
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
		break;
		
		// бандит в городе
		case "Beliz_townbandos":
			dialog.text = "Ei! O que você quer? Eu não estava esperando visita nenhuma. Cai fora!";
			link.l1 = "Por que tanta grosseria, amigo? Eu só queria perguntar...";
			link.l1.go = "Beliz_townbandos_1";
		break;
		
		case "Beliz_townbandos_1":
			dialog.text = "Não ouviu, não? Cai fora daqui agora, ou eu mesmo te jogo porta afora!";
			link.l1 = "Hum... Bem, talvez você seja mesmo a pessoa que estou procurando. Você parece nervoso demais, camarada...";
			link.l1.go = "Beliz_townbandos_2";
		break;
		
		case "Beliz_townbandos_2":
			dialog.text = "Pensa que é esperto demais, não é? Mais uma vez: ou você cai fora agora, ou eu chamo os guardas e eles te jogam na cadeia!";
			link.l1 = "Me jogar atrás das grades? Que interessante. Sabe, agora tenho quase certeza de que encontrei quem eu procurava. Tudo bem, eu concordo. Vamos chamar os guardas, e então caminhamos juntos até o gabinete do comandante, como uma família feliz. Acabei de passar por lá, então lembro o caminho... Guardas! GUARDAS!";
			link.l1.go = "Beliz_townbandos_3";
		break;
		
		case "Beliz_townbandos_3":
			dialog.text = "Vai se ferrar! Eu vou te atravessar!";
			link.l1 = "Oh ho-ho! Bem, pode tentar!";
			link.l1.go = "Beliz_townbandos_4";
		break;
		
		case "Beliz_townbandos_4":
			DialogExit();
			DeleteAttribute(npchar, "CityType");
			DeleteAttribute(npchar, "city"); // чтобы не было НЗГ
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_BelizTownbandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.Caleuche_letter.win_condition.l1 = "item";
			pchar.quest.Caleuche_letter.win_condition.l1.item = "kaleuche_letter";
			pchar.quest.Caleuche_letter.function = "Caleuche_FindLetter";
		break;
		
		// главарь лесных бандосов
		case "Beliz_forestbandos":
			dialog.text = "Ei, viajante! Seja bem-vindo, seja bem-vindo... Jantar, hospedagem - tudo pelo seu dinheiro. Então, prepare-se para virar os bolsos do avesso!";
			link.l1 = "Calma aí, meu bom homem. Tenho assuntos a tratar com você.";
			link.l1.go = "Beliz_forestbandos_1";
		break;
		
		case "Beliz_forestbandos_1":
			dialog.text = "Negócios? Ha-ha! O único negócio que você tem aqui é entregar toda a sua prata e ouro!";
			link.l1 = "Cala a boca. Eu trouxe a carta de Belize que você estava esperando. O mensageiro não conseguiu passar pelos guardas e me confiou o assunto.";
			link.l1.go = "Beliz_forestbandos_2";
		break;
		
		case "Beliz_forestbandos_2":
			dialog.text = "Mostre-me!";
			link.l1 = "Aqui...";
			link.l1.go = "Beliz_forestbandos_3";
		break;
		
		case "Beliz_forestbandos_3":
			Log_Info("You have given a note");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "kaleuche_letter", 1);
			dialog.text = "(lendo) Hm... Isso é realmente estranho... Como você se envolveu nisso?";
			link.l1 = "Já te falei, prenderam o seu homem, então eu fiquei com o trabalho dele. Ele prometeu dinheiro e uma recepção calorosa da sua parte...";
			link.l1.go = "Beliz_forestbandos_4";
		break;
		
		case "Beliz_forestbandos_4":
			dialog.text = "A warm welcome? Alright, pal. We'll warm you up, feed you, give you money and all that stuff - but you, you too, will have to prove us that you're not a guards' hound. We've got a score to settle now\nA merchant has recently arrived to a nearby cove; apparently, he wants to sneak into the city with his wares past the customs office. But we will still exact the duty from him. We are lawful folk after all! You'll come with us. Do you know which end of the sword goes where?";
			link.l1 = "E eu vou receber uma parte dessa tarefa?";
			link.l1.go = "Beliz_forestbandos_5";
		break;
		
		case "Beliz_forestbandos_5":
			dialog.text = "Com certeza você vai! Se for corajoso na batalha e se sair vivo. Mas não espere moleza, o mercador não está sozinho, ele tem escolta, e uma escolta bem grande. Bem, hora de ir – nossa presa está perto. Rapazes! Preparem suas armas, estamos partindo!";
			link.l1 = "...";
			link.l1.go = "Beliz_forestbandos_6";
		break;
		
		case "Beliz_forestbandos_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload3_back", true);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Beliz_forestbandos_"+i);	
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "goto", "goto"+(rand(1)+1), "", 10.0);
			}
			DoQuestCheckDelay("OpenTheDoors", 12.0);
			pchar.quest.Caleuche_bandosrobb.win_condition.l1 = "location";
			pchar.quest.Caleuche_bandosrobb.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.Caleuche_bandosrobb.function = "Caleuche_JungleBandosRobbery";
		break;
		
		case "Beliz_forestbandos_7":
			dialog.text = "Vejo que você não é covarde. Muito bem! Você ganhou sua parte. Como prefere receber? Dinheiro? Mercadorias? Eles carregavam muito álcool, vai render um bom dinheiro.";
			link.l1 = "Dinheiro.";
			link.l1.go = "Beliz_forestbandos_8_1";
			link.l2 = "Mercadorias.";
			link.l2.go = "Beliz_forestbandos_8_2";
		break;
		
		case "Beliz_forestbandos_8_1":
			Log_Info("You have received 100 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Aqui está! E esta bolsa é pela entrega da carta.";
			link.l1 = "Obrigado! Agora sim, é do jeito que eu gosto!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_8_2":
			Log_Info("You have received 30 bottles of rum");
			Log_Info("You have received 12 bottles of wine");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "potionrum", 30);
			TakeNItems(pchar, "potionwine", 12);
			dialog.text = "Aqui está! Só não vá beber até morrer, ha-ha-ha! E essa bolsa é pelo serviço de entregar a carta.";
			link.l1 = "Obrigado! Agora sim, do jeito que eu gosto!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_9":
			Log_Info("You have received a purse");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "purse2", 1);
			dialog.text = "Você me parece um sujeito decente. Que tal outro serviço? É sobre aquela carta que você mandou entregar pra mim.";
			link.l1 = "Claro.";
			link.l1.go = "Beliz_forestbandos_10";
		break;
		
		case "Beliz_forestbandos_10":
			dialog.text = "Então venha para a caverna. São duas. Entre na selva até o lugar onde nos encontramos da última vez, depois pegue o caminho da esquerda. Nos reunimos em três dias na entrada da caverna, da meia-noite à uma. Entendeu? Se você se comportar, vamos aceitar você na nossa gangue. Mas lembre-se – se você abrir a boca na cidade, está acabado. Eu tenho braços longos.";
			link.l1 = "Para de me assustar, já entendi. Vou ficar quieto como um peixe. Me espera em três dias, eu vou estar lá. Eu adoro dinheiro fácil!";
			link.l1.go = "Beliz_forestbandos_11";
		break;
		
		case "Beliz_forestbandos_11":
			dialog.text = "Tá certo, camarada. Agora cai fora antes que os guardas apareçam. A gente também vai embora.";
			link.l1 = "Até mais, camarada...";
			link.l1.go = "Beliz_forestbandos_12";
		break;
		
		case "Beliz_forestbandos_12":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload2_back", false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload3_back", false);
			LocatorReloadEnterDisable("Beliz_CaveEntrance_2", "reload1_back", true); // закрываем пещеру
			SetFunctionTimerCondition("Caleuche_CaveOpen", 0, 0, 1, false); // таймер
			SetFunctionTimerCondition("Caleuche_BelizbandosClear", 0, 0, 4, false); // таймер
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			for (i=1; i<=6; i++)
			{
				if (GetCharacterIndex("Beliz_forestbandos_"+i) != -1)
				{
					sld = characterFromId("Beliz_forestbandos_"+i);	
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "TMP_FRIEND");
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "OpenTheDoors", 20.0);
				}
			}
			AddQuestRecord("Caleuche", "13");
			// костер
			ref location = &Locations[FindLocation("Beliz_Jungle_01")];
			DeleteAttribute(location, "fire");
			sld = ItemsFromID("fire");
			sld.shown = false;
			// пакуем схрон в пещере
			pchar.GenQuestBox.Beliz_Cave_2 = true;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.kaleuche_amulet2 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.suit4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse1 = 7; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse2 = 3; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potion2 = 10;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potionrum = 55;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.indian_3 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.obereg_4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.berserker_potion = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry2 = 15;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry3 = 33;
			// меняем флаг
			pchar.questTemp.Caleuche.Bandos = "know";
			SaveCurrentQuestDateParam("questTemp.Caleuche.belizbandos");
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
		break;
		
		// спалили бандосы в пещере
		case "Beliz_cavebandos":
			dialog.text = "O quê! Então resolveu se apossar do que é nosso? Não vai sair impune, seu verme imundo!";
			link.l1 = "Quem você acabou de chamar de verme, seu canalha?!";
			link.l1.go = "Beliz_cavebandos_1";
		break;
		
		case "Beliz_cavebandos_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Beliz_cavebandos_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_cavebandos_3", "citiz_23", "man", "man", 30, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 70, 70, "blade_10", "pistol1", "bullet", 150);
				ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster16");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_CaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// капитан гарпии
		case "reginald":
			dialog.text = "Olá, colega! O que te traz aqui?";
			link.l1 = TimeGreeting()+", senhor Jackson. Fico feliz por finalmente ter encontrado você.";
			link.l1.go = "reginald_1";
			DelLandQuestMark(npchar);
		break;
		
		case "reginald_1":
			dialog.text = "'Mynheer Jackson', ha-ha! Olha, pra ser sincero, logo eu mesmo vou me chamar assim. Trabalho pra essa maldita Companhia sem parar... mas eles pagam bem, muito bem!.. Então, o que te traz aqui, camarada?";
			link.l1 = "O nosso conhecido em comum, o faroleiro, me contou que você tinha um amuleto indígena antigo. Imagino que nunca tenha encontrado utilidade para ele, e eu estou precisando muito. Gostaria de comprá-lo de você.";
			link.l1.go = "reginald_2";
		break;
		
		case "reginald_2":
			dialog.text = "Ah, você está falando daquele enfeite bonito que perguntei para o contramestre aposentado? É, amigo, você tem razão, nunca serviu pra nada mesmo, só é bonito de ver.";
			link.l1 = "Quanto você quer por isso?";
			link.l1.go = "reginald_3";
		break;
		
		case "reginald_3":
			dialog.text = "Veja bem, tem um pequeno problema... Deixe-me explicar. Eu não estou com isso agora. Como nunca encontrei utilidade, deixei no meu baú na praia, junto com minhas outras coisas.";
			link.l1 = "Ah, isso explica por que você ainda está... bem, deixa pra lá. Vamos logo até aquele seu baú, e eu compro o amuleto de você. Simples assim. Onde você guarda ele?";
			link.l1.go = "reginald_4";
		break;
		
		case "reginald_4":
			dialog.text = "Não é tão simples assim. Meu baú está em Barbados, na torre do farol, e está bem trancado para que ninguém possa se aproveitar dele na minha ausência. E sinto muito mesmo, mas não posso ir com você para Barbados. Pelo meu contrato com os holandeses, devo navegar entre Philipsburg e Port Royal e seguir o cronograma à risca. E Barbados não fica nem perto dessa rota.";
			link.l1 = "E o que podemos fazer? Eu preciso mesmo, de verdade, desse amuleto!";
			link.l1.go = "reginald_5";
		break;
		
		case "reginald_5":
			dialog.text = "Hmm... Bem, existe uma opção. Eu te dou a chave do meu baú, e você navega até Barbados sozinho. Mas você vai ter que me compensar por tudo o que está lá dentro, e aí pode ficar com eles. Me desculpe pela desconfiança – mas você precisa entender. Nunca te vi antes.";
			link.l1 = "Quanto?";
			link.l1.go = "reginald_6";
		break;
		
		case "reginald_6":
			dialog.text = "Quinhentas moedas de ouro. Nem uma a menos.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Está aqui! Aqui está seu ouro.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Hum... Eu não tenho tantas moedas de ouro comigo.";
			link.l2.go = "reginald_7";
		break;
		
		case "reginald_7":
			dialog.text = "Então venha me procurar de novo quando conseguir o dinheiro. Se me encontrou uma vez, vai me encontrar de novo. Estarei navegando entre St. Martin e a Jamaica por um bom tempo ainda.";
			link.l1 = "Certo, combinado.";
			link.l1.go = "reginald_8";
		break;
		
		case "reginald_8":
			DialogExit();
			NextDiag.CurrentNode = "reginald_9";
			npchar.DeckDialogNode = "reginald_9";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "reginald_9":
			dialog.text = "Você de novo, amigo? Tem 500 moedas?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Sim. Aqui está o seu ouro.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Ainda não, mas estou trabalhando nisso.";
			link.l2.go = "reginald_8";
		break;
		
		case "reginald_10":
			RemoveDublonsFromPCharTotal(500);
			DelLandQuestMark(npchar);
			
			dialog.text = "Ótimo! E aqui está sua chave. Só te peço uma coisa: depois que pegar tudo o que tem lá dentro, por favor, deixe a chave na fechadura. Eu detestaria ter que encomendar uma nova fechadura e chave para ela.";
			link.l1 = "Certo.";
			link.l1.go = "reginald_11";
		break;
		
		case "reginald_11":
			dialog.text = "Então boa sorte pra você, amigo! Boa viagem!";
			link.l1 = "E o mesmo para você... Boa viagem, senhor Jackson!";
			link.l1.go = "reginald_12";
		break;
		
		case "reginald_12":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_SpawnItemsInTheChest");
			AddQuestRecord("Caleuche", "20");
		break;
		
		case "Caleuche_Reginald_21":
			dialog.text = "O que diabos você quer de nós? Este é um navio da Companhia Holandesa das Índias Ocidentais, e truques como esse não ficam sem punição. Eles vão caçar você até os confins da terra – você e sua corja.";
			link.l1 = "Não dou a mínima para os holandeses ou a companhia deles. O que eu quero é um antigo amuleto indígena, e eu sei que você está com ele – ou já esteve.";
			link.l1.go = "Caleuche_Reginald_22";
		break;

		case "Caleuche_Reginald_22":
			dialog.text = "Você está louco! Atacar um navio por causa de uma bugiganga?";
			link.l1 = "Cala a boca e entrega logo, talvez você saia vivo dessa.";
			link.l1.go = "Caleuche_Reginald_23";
		break;

		case "Caleuche_Reginald_23":
			dialog.text = "Maldito seja... Eu não ando com isso. Está em Barbados.";
			link.l1 = "Então seu barco furado vai afundar agora mesmo, e você vai fazer companhia pros ratos no meu porão. Vamos ter bastante tempo no caminho pra você me contar exatamente onde encontrar isso. E pode confiar – tenho uns rapazes a bordo que sabem fazer até o mais teimoso abrir o bico... sem precisar de gentilezas.";
			link.l1.go = "Caleuche_Reginald_24";
		break;

		case "Caleuche_Reginald_24":
			dialog.text = "Não precisa disso. Está em um baú no farol. Trancado. Aqui está a chave.";
			link.l1 = "Escolha inteligente, camarada. Pena que mais gente como você não tenha a cabeça para fazer o mesmo... me pouparia de muito sangue nas mãos.";
			link.l1.go = "Caleuche_Reginald_24_1";
			link.l2 = "Você fez uma escolha sensata. Mas veja... Não posso deixar você viver. Você iria correndo contar tudo àqueles mercadores holandeses, e eu prefiro não chamar a atenção deles.";
			link.l2.go = "Caleuche_Reginald_24_2";
		break;
		
		case "Caleuche_Reginald_24_1":
			dialog.text = "Aquele baú guarda tudo o que conquistei servindo aos holandeses ao longo dos anos...";
			link.l1 = "Então vamos fechar assim: o baú fica comigo, e você mantém sua pele preciosa. Justo o bastante...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_EndFightWithReginald");
		break;
		
		case "Caleuche_Reginald_24_2":
			dialog.text = "Argh...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_KillToReginald");
		break;
		
		// монах в Виллемстаде
		case "monk_caleuche":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("villemstad");
			npchar.lifeday = 1;
			dialog.text = "Olá, Capitão "+GetFullName(pchar)+" Fico feliz em recebê-lo em Willemstad.";
			link.l1 = "Olá, padre. Eu não me lembro de você. Nós nos conhecemos?";
			link.l1.go = "monk_caleuche_1";
		break;
		
		case "monk_caleuche_1":
			dialog.text = "Fiz algumas perguntas sobre você assim que seu navio atracou. E acho que posso pedir sua ajuda.";
			link.l1 = "Muito interessante. E por que eu?";
			link.l1.go = "monk_caleuche_2";
		break;
		
		case "monk_caleuche_2":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Porque você fez muito pela República das Províncias Livres. Você tem uma boa reputação com a Companhia e é amigo do governador. Já recorri a várias autoridades e fui rejeitado, mas espero que uma pessoa nobre como você não recuse um humilde pedido de um servo do nosso Senhor.";
			}
			else
			{
				dialog.text = "Porque você não está a serviço do nosso governador. Não trabalha para a Companhia e não tem ligação com os nossos militares – caso contrário, provavelmente só me ignoraria como uma mosca incômoda, já que eu já recorri a várias autoridades e fui rejeitado.";
			}
			link.l1 = "Certo, então. Qual é o motivo do seu pedido?";
			link.l1.go = "monk_caleuche_3";
		break;
		
		case "monk_caleuche_3":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Tem uma casa nos fundos do banco. Uma senhora que morava lá estava alugando um quarto para um sujeito muito suspeito, que não era daqui, e também não era o holandês. E então nosso padre superior, Padre "+sld.name+", tinha reconhecido ele\nEra Joachim Merriman, um português acusado pela Inquisição de feitiçaria e pacto com forças profanas. Ele se escondeu da Inquisição no Novo Mundo. Sabe, os espanhóis costumam acusar de heresia e feitiçaria quem cai em desgraça, só pra queimar na fogueira, mas... Nesse caso, eles estavam certos. Merriman é um feiticeiro\nEntão, ele morou em Willemstad por um tempo, e depois sumiu tão de repente quanto apareceu. E algum tempo depois, uma mulher, aquela que alugou o quarto pra ele, nunca mais foi vista saindo daquela casa. Nunca! E desde então, ninguém mais viu ela em lugar nenhum\nE à noite, às vezes dá pra ver luzes vermelhas e azuis piscando nas janelas do segundo andar e ouvir sons estranhos, quase como gritos profanos. Padre "+sld.name+" appealed to the commandant. He sent a patrol of four soldiers; they searched the house, but found nothing: neither the landlady herself, nor anyone else, nor anything suspicious at all\nBut these strange things keep happening. The landlady has never shown up, and this hellish light can still be seen there at night. Besides, two beggars have recently gone missing as well. I heard them talking at the parvis – they knew there were no owners in the house, so they decided to lodge there. No one has seen them since.";
			link.l1 = "Então, você quer que eu entre naquela casa e descubra o que realmente aconteceu?";
			link.l1.go = "monk_caleuche_4";
		break;
		
		case "monk_caleuche_4":
			dialog.text = "Exatamente, nobre senhor. Por favor, ajude a Santa Igreja. O comandante diz que estamos imaginando coisas, já que a patrulha dele nunca encontrou nada. O governo pensa do mesmo jeito. O povo simplesmente não liga, porque não vê isso como uma ameaça direta para eles.";
			link.l1 = "Hum... E eu preciso ir lá à noite?";
			link.l1.go = "monk_caleuche_5";
		break;
		
		case "monk_caleuche_5":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Yes, mynheer. It's quiet there during the day, that's why the soldiers didn't find anything. I think the commandant is afraid for his men; I would be too. But please, I beg of you. Father "+sld.name+" will thank you and reward you for your service. Once you've been to that den during the night, please tell him what you find there. I assure you, our misgivings are well-founded.";
			link.l1 = "Certo. Vou pensar nisso.";
			link.l1.go = "monk_caleuche_6";
		break;
		
		case "monk_caleuche_6":
			dialog.text = "Obrigada, capitão. Espero que não recuse meu humilde pedido. Por favor, faça isso em nome de nosso Senhor, de nossa fé e de tudo o que é sagrado. Vá com minha bênção.";
			link.l1 = "...";
			link.l1.go = "monk_caleuche_7";
		break;
		
		case "monk_caleuche_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "none", "", "", "", -1);
			AddQuestRecord("Caleuche", "24");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "visit the house of Joaquim Merriman, where, according to him, strange things happen at night. Remembering that special gleam in Merriman's eyes when he looked at the jade skull, I feel a little creepy. It seems that the old Jew could not resist the sum of half a million pesos. Whatever the case, I don`t feel like going to Merriman former abode at night.";
				else sTemp = "visit the house of my old acquaintance Joachim Merriman, where, allegedly, strange things are happening at nights. I still remember that glitter in Merriman's eyes, when he was looking at the skull, and honestly I feel frightened. I am not really fond of the idea to visit his former abode in the night, who knows what kind of devils lurk there.";
			}
			else sTemp = "visit the house at the back of the bank, where some Joachim Merriman had been renting a room. Apparently it is that warlock, of which Tuttuathapak was talking about. According to the monk, strange things are happening in this house in the night. I really feel uncomfortable about visiting the warlock's former home, who knows what kind of devils lurk there.";
			AddQuestUserData("Caleuche", "sText", sTemp);
			i = Findlocation("Villemstad_town");
			DeleteAttribute(&locations[i], "reload.l14.close_for_night");
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1.location = "Villemstad_houseSp1_room";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2 = "Hour";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.start.hour = 1.00;
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.finish.hour = 3.00;
			pchar.quest.Caleuche_villemstadhouse.function = "Caleuche_CreateJoakimSkel";
		break;
		
		// охотник у пещеры
		case "cavehunter":
			dialog.text = "Espere aí, amigo. É melhor não ir lá se você valoriza a sua vida.";
			link.l1 = "E qual é o esquema?";
			link.l1.go = "cavehunter_1";
		break;
		
		case "cavehunter_1":
			dialog.text = "Confie em mim, é melhor você não saber. Mas a Morte está logo ali na esquina, e eu juro pelo Livro que você não volta vivo, existem coisas além da sua imaginação.";
			link.l1 = "Bem, se você diz, não vou desafiar o destino. Obrigado pelo aviso.";
			link.l1.go = "cavehunter_2";
		break;
		
		case "cavehunter_2":
			dialog.text = "De nada. Fique longe daquele caminho.";
			link.l1 = "...";
			link.l1.go = "cavehunter_3";
		break;
		
		case "cavehunter_3":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_4":
			dialog.text = "Fique longe desse caminho, camarada.";
			link.l1 = "Sim, eu me lembro...";
			link.l1.go = "cavehunter_4_1";
		break;
		
		case "cavehunter_4_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_5":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Tem certeza de que quer ir até lá?";
			link.l1 = "Com certeza. "+sld.name+", o padre superior da igreja em Havana, me enviou aqui. Preciso descobrir o que está acontecendo e tomar as medidas necessárias.";
			link.l1.go = "cavehunter_6";
			DelLandQuestMark(npchar);
		break;
		
		case "cavehunter_6":
			dialog.text = "O que está acontecendo aqui? Acho que você vai tremer de medo quando vir com seus próprios olhos o que está acontecendo aqui.";
			link.l1 = "Você quer dizer os mortos-vivos?";
			link.l1.go = "cavehunter_7";
		break;
		
		case "cavehunter_7":
			dialog.text = "Sim. E é melhor você acreditar no que eu digo.";
			link.l1 = "E eu acredito em você. Já encontrei aquela coisa profana em Willemstad e a destruí. Agora vou entrar lá e acabar com toda a imundície que se esconde nesta caverna.";
			link.l1.go = "cavehunter_8";
		break;
		
		case "cavehunter_8":
			int icpy = GetOfficersQuantity(pchar);
			switch (icpy)
			{
				case 0:
					dialog.text = "Vai sozinho mesmo? Você tá pedindo pra morrer, amigo. Você não faz ideia de quantos daqueles estão lá. Bom, vá se quiser, e eu vou à igreja acender uma vela pela paz da sua alma.";
					link.l1 = "Não se apresse em me enterrar. Já passei por coisa pior.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 1:
					dialog.text = "Só vocês dois? Receio que não vão chegar muito longe. Vocês não fazem ideia de quantas dessas coisas estão lá fora. É suicídio.";
					link.l1 = "Você só não nos conhece direito, amigo. Saia do caminho, e nós vamos purificar esse antro profano.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 2:
					dialog.text = "Só vocês três? Vocês devem ser lutadores experientes para se arriscarem assim. Mas ainda temo que não consigam. Vocês não fazem ideia de quantas dessas coisas estão dentro daquela gruta.";
					link.l1 = "Você só não nos conhece direito, amigo. Afaste-se, e nós vamos purificar este antro profano.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 3:
					dialog.text = "Vejo que vocês não são covardes. Mas vocês realmente não fazem ideia de quantos deles existem. Numa situação dessas, cada homem faz diferença. Droga, vou com vocês e vou meter bala nessa escória com meu mosquete!";
					link.l1 = "Você é uma alma corajosa, amigo. Não vou recusar sua ajuda. Vamos!";
					link.l1.go = "cavehunter_9";
				break;
			}
		break;
		
		case "cavehunter_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		break;
		
		case "cavehunter_9":
			DialogExit();
			npchar.quest.caleuche = true;
			npchar.dialog.currentnode = "cavehunter_10";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			// закрываем локаторы выхода
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", true);
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", true);
		break;
		
		case "cavehunter_10":
			dialog.text = "Vamos! Morte aos malditos mortos-vivos!";
			link.l1 = "...";
			link.l1.go = "cavehunter_10_1";
		break;
		
		case "cavehunter_10_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_10";
		break;
		
		case "cavehunter_11":
			dialog.text = "Isso sim foi um verdadeiro massacre! Quem diria que tantos mortos estavam escondidos aqui! Bem, pelo menos agora podemos descansar... Por favor, conte isso ao seu superior, aquele que te enviou pra cá. Espero mesmo que a Inquisição vá fundo nisso depois do seu relatório. Lidar com mortos-vivos é com eles, afinal, eu sou só um caçador comum.";
			link.l1 = "Com certeza vou contar pra ele. Obrigado pela ajuda, amigo. Você é alguém raro, poucos teriam coragem de enfrentar a própria morte! Boa sorte!";
			link.l1.go = "cavehunter_exit";
		break;
		
		// солдат в крипте при провале
		case "cryptguard":
			dialog.text = "Fique onde está! Este lugar é proibido!";
			link.l1 = "Ehh... E o que tem lá dentro?";
			link.l1.go = "cryptguard_1";
		break;
		
		case "cryptguard_1":
			dialog.text = "Um feiticeiro perigoso foi encontrado lá. Somente os padres e os soldados que os acompanham podem entrar.";
			link.l1 = "Entendi. O feiticeiro foi preso?";
			link.l1.go = "cryptguard_2";
		break;
		
		case "cryptguard_2":
			dialog.text = "Não estou autorizado a responder a esse tipo de pergunta, señor. Está na hora de você ir embora.";
			link.l1 = "Beleza, entendi. Boa sorte!";
			link.l1.go = "cryptguard_3";
		break;
		
		case "cryptguard_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Caleuche", "31");
			CloseQuestHeader("Caleuche");
			pchar.questTemp.Caleuche = "end";
		break;
		
		// чавинави-вождь
		case "Chavinavi":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_01.wav");
			dialog.text = "Fique parado, humano! Você está bem no coração do templo, e já foi longe demais para voltar agora.";
			link.l1 = "Quem é você?!";
			link.l1.go = "Chavinavi_1";
		break;
		
		case "Chavinavi_1":
			dialog.text = "Eu sou o chefe dos Chavinavi, o guardião e protetor deste lugar sagrado. Você não é o primeiro a entrar neste templo, mas apenas dois homens e uma mulher conseguiram entrar e sair vivos antes de você. É só por isso que me dou ao trabalho de falar com você agora. Por que veio aqui, rosto-pálido?";
			link.l1 = "Eu trouxe uma relíquia antiga aqui, o crânio de jade. Cinquenta anos atrás, ele foi tirado de um templo indígena no interior do continente. Eu ia encontrar o santuário e devolver a relíquia ao seu deus.";
			link.l1.go = "Chavinavi_2";
		break;
		
		case "Chavinavi_2":
			dialog.text = "É estranho ouvir tais palavras de alguém como você. Não acredito em você. Vocês, de pele clara, estão sempre vindo para tirar algo, mas nunca devolvem nada.";
			link.l1 = "Eu não minto. Ao devolver o crânio, vou quebrar a maldição lançada sobre o capitão do navio fantasma que aterroriza o Mar do Caribe, tornando-o mortal novamente, e vou livrar o mundo dele de uma vez por todas.";
			link.l1.go = "Chavinavi_3";
		break;
		
		case "Chavinavi_3":
			dialog.text = "Como você sabe que nosso Deus vai acabar com essa maldição, cara-pálida? Nosso Deus fala com você?";
			link.l1 = "Não. Vim aqui seguindo o conselho de um grande xamã chamado Tuttuathapak. Segundo ele, o crânio é a chave da maldição, e este é o único templo do Caribe. E sabe de uma coisa? Acho mesmo que ele consegue conversar com os espíritos do passado. Talvez até com você, chefe dos guerreiros jaguar.";
			link.l1.go = "Chavinavi_4";
		break;
		
		case "Chavinavi_4":
			dialog.text = "Suas palavras me surpreendem, cara-pálida, mas ainda não posso confiar totalmente em você. No entanto, se você veio a este templo para devolver nossa relíquia, certamente nosso xamã deve ter lhe contado sobre este lugar, sua criação, sua história e seus habitantes\nSe for assim, você responderá facilmente a todas as minhas perguntas. Então admitirei que você foi sincero comigo, permitirei que siga adiante e, além disso, o recompensarei.";
			link.l1 = "Então pergunte!";
			link.l1.go = "question1";
		break;
		
		case "question1":
			dialog.text = "I am the chieftain of the Chavinavi, and the jaguar warriors. Thousand years ago I was human; now I am carrying out my sacred duty in these chambers. Which god commands me?";
			link.l1 = "Mictlantecuhtli.";
			link.l1.go = "question1_l";
			link.l2 = "Kukulcan.";
			link.l2.go = "question1_l";
			link.l3 = "Yum Cimil.";
			link.l3.go = "question1_r";
			link.l4 = "Inti.";
			link.l4.go = "question1_l";
			link.l5 = "Kauil.";
			link.l5.go = "question1_l";
		break;
		
		case "question1_r":
			dialog.text = "Antes de seu povo de rosto pálido chegar, toda esta terra, das grandes neves ao norte até as vastas planícies ao sul, pertencia a nós, irmãos de uma só família...";
			link.l1 = "";
			link.l1.go = "question2";
		break;
		
		case "question1_l":
			dialog.text = "Antes do povo de rosto pálido chegar, toda esta terra, das grandes neves do norte às vastas planícies do sul, pertencia a nós, irmãos de uma só família...";
			link.l1 = "";
			link.l1.go = "question2";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question2":
			dialog.text = "Que tribo indígena construiu este templo?";
			link.l1 = "Inca.";
			link.l1.go = "question2_l";
			link.l2 = "Chavins.";
			link.l2.go = "question2_r";
			link.l3 = "Maya.";
			link.l3.go = "question2_l";
			link.l4 = "Asteca.";
			link.l4.go = "question2_l";
			link.l5 = "Arawak.";
			link.l5.go = "question2_l";
		break;
		
		case "question2_r":
			dialog.text = "Nosso povo avançou, ganhou sabedoria e conquistou novas florestas, planícies e ilhas. O povo que construiu este templo veio das matas do outro lado do Grande Mar...";
			link.l1 = "";
			link.l1.go = "question3";
		break;
		
		case "question2_l":
			dialog.text = "Nosso povo avançou, ganhou sabedoria e conquistou novas florestas, planícies e ilhas. O povo que construiu este templo veio das matas do outro lado do Grande Mar...";
			link.l1 = "";
			link.l1.go = "question3";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question3":
			dialog.text = "Quem liderou o grupo dessas pessoas gloriosas?";
			link.l1 = "Grande chefe.";
			link.l1.go = "question3_l";
			link.l2 = "Grande sacerdote.";
			link.l2.go = "question3_l";
			link.l3 = "Filho do grande cacique.";
			link.l3.go = "question3_r";
			link.l4 = "Filho do grande sacerdote.";
			link.l4.go = "question3_l";
			link.l5 = "O grupo não tinha líder.";
			link.l5.go = "question3_l";
		break;
		
		case "question3_r":
			dialog.text = "Os índios, guerreiros valentes e grandes viajantes, sempre amaram e respeitaram sua terra natal, mesmo depois de se estabelecerem em outro lugar. Como prova desse amor, construíram uma estátua no templo em forma de pássaro, símbolo de sua terra. Ela está atrás de mim...";
			link.l1 = "";
			link.l1.go = "question4";
		break;
		
		case "question3_l":
			dialog.text = "Os índios, guerreiros valentes e viajantes, sempre amaram e respeitaram sua terra natal, mesmo depois de se estabelecerem em outro lugar. Como prova desse amor, construíram uma estátua no templo em forma de pássaro, símbolo de sua terra. Ela está atrás de mim...";
			link.l1 = "";
			link.l1.go = "question4";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question4":
			dialog.text = "Qual é o nome desse pássaro?";
			link.l1 = "Albatroz.";
			link.l1.go = "question4_l";
			link.l2 = "Eagle.";
			link.l2.go = "question4_l";
			link.l3 = "Abutre.";
			link.l3.go = "question4_l";
			link.l4 = "Roc.";
			link.l4.go = "question4_l";
			link.l5 = "Condor.";
			link.l5.go = "question4_r";
		break;
		
		case "question4_r":
			dialog.text = "Anos de prosperidade vieram e se foram, desaparecendo como a chama de uma lamparina, e a vida abandonou a ilha. Só o templo permanece aqui como lembrança do grande poder dos antigos índios. O último xamã deixou um orbe solar sagrado sobre um pedestal, que dava força aos corajosos e castigava os perversos. Ele foi levado pelo homem que esteve aqui antes de você.";
			link.l1 = "";
			link.l1.go = "question5";
		break;
		
		case "question4_l":
			dialog.text = "Anos de prosperidade vieram e se foram, sumindo como a chama de uma lamparina, e a vida abandonou a ilha. Só o templo permanece aqui, lembrando o grande poder dos antigos índios. O último xamã deixou um orbe solar sagrado sobre um pedestal, que dava força aos valentes e castigava os perversos. Ele foi levado pelo homem que esteve aqui antes de você.";
			link.l1 = "";
			link.l1.go = "question5";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question5":
			dialog.text = "Qual era o nome daquele orbe sagrado?";
			link.l1 = "Orbe do sol radiante.";
			link.l1.go = "question5_l";
			link.l2 = "Orbe dos raios do sol.";
			link.l2.go = "question5_l";
			link.l3 = "Orbe do sol do meio-dia.";
			link.l3.go = "question5_l";
			link.l4 = "Orbe do sol nascente.";
			link.l4.go = "question5_r";
			link.l5 = "Orbe do sol poente.";
			link.l5.go = "question5_l";
		break;
		
		case "question5_r":
			if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
			{
				PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
				dialog.text = "Respostas erradas mostram que você mentiu para mim, homem branco! Você veio com más intenções! Conseguiu passar pelos guardiões do templo e do santuário, descobriu como funciona o mecanismo da porta – mas ainda assim não vai escapar de um combate mortal comigo. Prepare-se para morrer, cara pálida!";
				link.l1 = "Bem, se você insiste - vamos ver o quão grande guerreiro você é...";
				link.l1.go = "chavinavi_fight";
			}
			else
			{
				dialog.text = "O seu conhecimento sobre o meu povo e o meu templo lhe faz jus, cara-pálida. Agora eu acredito em você. Vá e cumpra aquilo pelo qual veio até aqui. Coloque a relíquia sagrada no pedestal diante do condor, onde antes repousava o orbe do sol nascente\nDepois volte para mim. Sua devoção a Yum Cimil e sua decisão de devolver voluntariamente aquilo que foi roubado pelos seus irmãos devem ser recompensadas.";
				link.l1 = "Obrigado pela sua confiança, grande chefe.";
				link.l1.go = "chavinavi_exit";
			}
		break;
		
		case "question5_l":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
			dialog.text = "Respostas erradas mostram que você mentiu para mim, homem branco! Você veio com más intenções! Conseguiu passar pelos guardiões do templo e do santuário, descobriu como funciona o mecanismo da porta – mas ainda assim não vai escapar de um combate mortal comigo. Prepare-se para morrer, cara pálida!";
			link.l1 = "Bem, se você insiste - vamos ver o quão grande guerreiro você é...";
			link.l1.go = "chavinavi_fight";
		break;
		
		case "chavinavi_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_TopChavinaviDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "chavinavi_exit":
			DialogExit();
			sld = ItemsFromID("SkullAztec");
			sld.shown = "0";
			sld.useLocation = "KhaelRoa_Treasure_Alcove";
			sld.useLocator = "button01";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "Chavinavi_5":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_03.wav");
			dialog.text = "Você fez como prometeu, cara-pálida. Fico feliz que você não seja um mentiroso como a maioria dos seus irmãos. Também cumprirei minha palavra. Aqui, aceite este presente meu – o símbolo do poder dos guerreiros jaguar. O próprio Yum Cimil infundiu esta pele com parte de sua força.";
			link.l1 = "Caramba! Isso é tão lindo!";
			link.l1.go = "Chavinavi_6";
		break;
		
		case "Chavinavi_6":
			GiveItem2Character(pchar, "KhaelRoa_item");
			Log_Info("You have received jaguar's pelt");
			PlaySound("interface\important_item.wav");
			dialog.text = "Esta não é uma pele comum. Quando você a vestir, ganhará a força do guerreiro jaguar. O poder da sua arma, que cospe fogo e dispara chumbo, aumentará dez vezes, e você será capaz de cobrir o campo de batalha com os corpos dos seus inimigos\nMas nenhum mortal pode suportar o poder que Yum Cimil colocou nesta pele. Assim que você o liberar, ele ficará com você apenas até a próxima meia-noite, e então desaparecerá. Cuide bem dela, cara-pálida, e não desperdice seu poder em uma briga insignificante.";
			link.l1 = "Obrigado! Só vou usar quando estiver completamente cercado pelos inimigos.";
			link.l1.go = "Chavinavi_7";
		break;
		
		case "Chavinavi_7":
			dialog.text = "Agora vá. E avise seus irmãos para não perturbarem a serenidade destas câmaras sagradas. Os guerreiros jaguar não têm piedade dos rostos-pálidos e não lhes darão trégua.";
			link.l1 = "Adeus, chefe.";
			link.l1.go = "Chavinavi_8";
		break;
		
		case "Chavinavi_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Caleuche", "38");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeIndianRelation(10.0);
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
