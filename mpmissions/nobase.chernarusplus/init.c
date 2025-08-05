void main()
{
    //INIT ECONOMY--------------------------------------
    Hive ce = CreateHive();
    if ( ce )
        ce.InitOffline();
    //DATE RESET AFTER ECONOMY INIT-------------------------
    int year, month, day, hour, minute;
    int reset_month = 9, reset_day = 20;
    GetGame().GetWorld().GetDate(year, month, day, hour, minute);

    if ((month == reset_month) && (day < reset_day))
    {
        GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
    }
    else
    {
        if ((month == reset_month + 1) && (day > reset_day))
        {
            GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
        }
        else
        {
            if ((month < reset_month) || (month > reset_month + 1))
            {
                GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
            }
        }
    }
    //GetCEApi().ExportProxyData(Vector(7500, GetGame().SurfaceY(7500, 7500), 7500), 20000);
}

class CustomMission: MissionServer
{
    void SetRandomHealth(EntityAI itemEnt)
    {
        if ( itemEnt )
        {
            float rndHlt = Math.RandomFloat( 0.45, 0.65 );
            itemEnt.SetHealth01( "", "", rndHlt );
        }
    }

    override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
    {
        Entity playerEnt;
        playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
        Class.CastTo( m_player, playerEnt );
        GetGame().SelectPlayer( identity, m_player );
        return m_player;
    }

    override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
    {   
        player.ClearInventory();          //LIMPAR INVENTÁRIO INICIAL
        
        //ROUPAS
        string PantstArray[] = {"Jeans_Black"};
        string ShoesArray[] = {"AthleticShoes_Black","AthleticShoes_Grey","AthleticShoes_Green","AthleticShoes_Brown"};     
        player.GetInventory().CreateInInventory("OZ_Tshirt_Black");
        player.GetInventory().CreateInInventory(PantstArray[Math.RandomInt(0,0)]);
        player.GetInventory().CreateInInventory(ShoesArray[Math.RandomInt(0,4)]);
        //ITEMS
        // string ChemlightArray[] = {"Chemlight_White","Chemlight_Yellow","Chemlight_Green","Chemlight_Red"};
        string FoodArray[] = {"Plum","Apple","Pear"};        
        string DrinkArray[] = {"SodaCan_Cola","SodaCan_Pipsi","SodaCan_Spite","SodaCan_Fronta"};            
        player.GetInventory().CreateInInventory("SteakKnife");
        player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("ChernarusMap");
        player.GetInventory().CreateInInventory(FoodArray[Math.RandomInt(0,3)]);
        player.GetInventory().CreateInInventory(DrinkArray[Math.RandomInt(0,4)]);
        
        
        player.GetStatEnergy().Set(750); //FOME INICIAL
        player.GetStatWater().Set(750);  //SEDE INICIAL
    }   
};

Mission CreateCustomMission(string path)
{
    return new CustomMission();
}